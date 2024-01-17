#include "const.h"
#include "common_utils.h"



char setParamNavigationTelemerty(char param)
{
    //������� ����������� ������� ���������� ��������� ������������� ����������
    // 0 - �������� ���� ��� ��� ��������� ��������
    // 1 - 1��, 2 - 2 ��, 3 - 5 ��, 4 - 10 ��, 5 - 20 ��.
    // ���������� 0 ��� 0�10 - ������������ �������
    return 0;
}

char getParamNavigationTelemerty()
{
    //�������� ����������� ������� ���������� ��������� ������������� ����������
    // 0 - �������� ���������
    // 1 - 1��, 2 - 2 ��, 3 - 5 ��, 4 - 10 ��, 5 - 20 ��.

    return 0x05;
}
// ������� 0�02
void handlerNavigationTelemetryCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerNavigationTelemetryCommand working\n ");

    switch(input_data->header[1])// ������� ������������
    {
    case 0: //������� �� ��������� ����������
    {

        char param = input_data->body[0];
        char status = setParamNavigationTelemerty(param);
        char body[5] = {36, 0x02, 0x03, 0x01,status};
        char crc = crcCalc(body, 5);
        char response[6] = {36, 0x02, 0x03, 0x01,status,crc};
        sendResponse(response,6);
        break;
    }


    case 1: //������ ���������
    {
        char param = getParamNavigationTelemerty();
        char body[6] = {36, 0x03, 0x03, 0x02, 0x01, param};
        char crc = crcCalc(body, 6);
        char response[7] = {36, 0x03, 0x03, 0x02, 0x01, param, crc};
        sendResponse(response,7);
        break;
    }
    }
}









//
//    float float_value = 43.5678;
//    char float_bytes[sizeof(float)];
//    memcpy(float_bytes, &float_value, sizeof(float));
