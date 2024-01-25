#include "const.h"
#include "common_utils.h"

char setDevicesForSolution(char devices)
{
    //������������� ���������� ����������� � �������. ���� ������� 0 ����� 0�10 ������������ ����� ���������
    return 0;
}

char getDevicesForSolution()
{
    //�������� ���������� ����������� � �������
    //0x1E ��� ����
    return 0x1F;
}
// ������� 0�01
void handlerDevicesForSolutionCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerDevicesForSolutionCommand working\n ");

    switch(input_data->header[1])// ������� ������������
    {
    case 0: //������� �� ��������� ����������
    {
        char param = input_data->body[0];
        char status = setDevicesForSolution(param);
        char body[6] = {36, 0x02, 0x01, 0x00,0x01,status};
        char crc = crcCalc(body, 5);
        char response[7] = {36, 0x02, 0x01, 0x00,0x01,status,crc};
        sendResponse(response,7);
        break;
    }


    case 1: //������ ���������
    {
        char devices = getDevicesForSolution();
        char body[7] = {36, 0x03, 0x01, 0x00,0x02, 0x01, devices};
        char crc = crcCalc(body, 7);
        char response[8] = {36, 0x03, 0x01,0x00, 0x02, 0x01, devices, crc};
        sendResponse(response,8);
        break;
    }
    }
}


