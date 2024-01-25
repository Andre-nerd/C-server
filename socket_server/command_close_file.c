#include "const.h"
#include "common_utils.h"

char closeFileByDescriptor(char descriptor){
    // ��������� ���� �� �����������

    return 0x00;
}

// ������� 0�06
void handlerCloseFileWriteCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerCloseFileWriteCommand working\n ");
    // ��������� ���� �� �����������
    char descriptor = input_data->body[0];
    char status = closeFileByDescriptor(descriptor);

    //��������� �������� �����. �� ��������� ���������� ������ ����� �� �������, ������������ 0�02
    unsigned char response[7] = {36,0x02,0x06,0x00,0x01,status};
    unsigned char crc = crcCalc(response, 6);
    response[6] = crc;
    sendResponse(response,7);

}


