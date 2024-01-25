#include "const.h"
#include "common_utils.h"

// ������� 0�00
void handlerOnOffCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerOnOffCommand working\n ");

    //��������� �������� �����. �� ��������� ���������� ������ ����� �� �������, ������������ 0�02
    unsigned char shortResponse[6] = {36,0x02,0x00,0x00,0x01,0x00};
    int res = -1;
    if(input_data->header[1] == direction)
    {
        res = setModeOnOff((int)input_data->body[0]);
    }
    if(res != 0)
    {
        shortResponse[5] = 0x10; // ������������ �����
    }

    unsigned char crc = crcCalc(shortResponse, 5);
    unsigned char response[7] = {36,0x02,0x00,0x00,0x01,shortResponse[5],crc};
    sendResponse(response,7);

}

int setModeOnOff(int mode)
{
    int res = -1;
    switch(mode)
    {
    case 0:// ��������� ������
        res = offMode();
        break;

    case 1://����������� ������
        res = resetMode();
        break;
    }
    return res;
}

int offMode()
{
    //��������� ������, ���� ������� �� ���������� ����
    return 0;
}

int resetMode()
{
    //����������� ������, ���� ������� �� ���������� ����
    return 0;
}
