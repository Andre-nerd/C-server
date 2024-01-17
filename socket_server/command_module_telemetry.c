#include "const.h"
#include "common_utils.h"

char setParamModuleTelemerty(char param)
{
    //������� ����������� ������� ���������� ��������� ���������� ������
    // 0 - �������� ���� ��� ��� ��������� ��������
    // 1 - 1��, 2 - 2 ��, 3 - 5 ��, 4 - 10 ��, 5 - 20 ��.
    // ���������� 0 ��� 0�10 - ������������ �������
    return 0;
}

char getParamModuleTelemerty()
{
    //�������� ����������� ������� ���������� ��������� ���������� ������
    // 0 - �������� ���������
    // 1 - 1��, 2 - 2 ��, 3 - 5 ��, 4 - 10 ��, 5 - 20 ��.

    return 0x03;
}
// ������� 0�02
void handlerModuleTelemetryCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerModuleTelemetryCommand working\n ");

    switch(input_data->header[1])// ������� ������������
    {
    case 0: //������� �� ��������� ����������
    {

        char param = input_data->body[0];
        char status = setParamModuleTelemerty(param);
        char body[5] = {36, 0x02, 0x04, 0x01,status};
        char crc = crcCalc(body, 5);
        char response[6] = {36, 0x02, 0x04, 0x01,status,crc};
        sendResponse(response,6);
        break;
    }


    case 1: //������ ���������
    {
        char param = getParamModuleTelemerty();
        char body[6] = {36, 0x03, 0x04, 0x02, 0x01, param};
        char crc = crcCalc(body, 6);
        char response[7] = {36, 0x03, 0x04, 0x02, 0x01, param, crc};
        sendResponse(response,7);
        break;
    }
    }
}
