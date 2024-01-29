#include "const.h"
#include "common_utils.h"

char setSubscribeAmendment(STRUCT_COMMAND *input_data)
{
    //������������� �� RTK ��� PPP
    // ��� ��������� ������ ���������, ip, port, mountPoint, userId, userPassword
    int ptr = 0;
    char source = input_data->body[ptr]; // 1- RTK , 2- PPP
    printf("source = %d\n", source);
    ptr++;

    char l1 = input_data->body[ptr]; //����� ������ Ip ������
    printf("length Ip string: %d \n", l1);
    ptr++;
    printf("IP: \n");
    char* ip = (char*) malloc(l1);
    for(int i = 0; i < l1; ++i){
        ip[i] = input_data->body[i+2];
        printf("%c", ip[i]);
    }
    printf("\n");
    ptr += l1;

    int* port = &input_data->body[ptr];
    printf("Port: %d \n", *port);
    ptr +=4;

    char l2 = input_data->body[ptr]; //����� ����� ����� ������������
    printf("Mount point length: %d \n", l2);
    ptr++;
    char* mountPoint = (char*) malloc(l2);
    for(int i = 0; i < l2; ++i){
        mountPoint[i] = input_data->body[ptr+i];
        printf("%c", mountPoint[i]);
    }
    printf("\n");
    ptr +=l2;

    char l3 = input_data->body[ptr]; //����� userId
    printf("User id length: %d \n", l3);
    ptr++;
    char* userId = (char*) malloc(l3);
    for(int i = 0; i < l3; ++i){
        userId[i] = input_data->body[ptr+i];
        printf("%c", userId[i]);
    }
    printf("\n");
    ptr +=l3;

    char l4 = input_data->body[ptr]; //����� password user
    printf("User password length: %d \n", l4);
    ptr++;
    char* userPassword = (char*) malloc(l4);
    for(int i = 0; i < l4; ++i){
        userPassword[i] = input_data->body[ptr+i];
        printf("%c", userPassword[i]);
    }
    printf("\n");
    ptr +=l4;


    free(userId);
    free(mountPoint);
    free(ip);
    return 0;
}

char getSubscribedAmendment()
{
    //�������� ����������� ��������

    return 0x07;
}
// ������� 0�08
void handlerSubscribeAmendmentCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerSubscribeAmendmentCommand working\n ");

    switch(input_data->header[1])// ������� ������������
    {
    case 0: //������� �� ��������� ����������
    {
        char status = setSubscribeAmendment(input_data);
//        char body[6] = {36, 0x02, 0x02, 0x00, 0x01,status};
//        char crc = crcCalc(body, 5);
//        char response[7] = {36, 0x02, 0x02, 0x00,0x01,status,crc};
//        sendResponse(response,7);
        break;
    }
    case 1: //������ ���������
    {
//        char param = getAmendment();
//        char body[7] = {36, 0x03, 0x02, 0x00, 0x02, 0x01, param};
//        char crc = crcCalc(body, 6);
//        char response[8] = {36, 0x03, 0x02,0x00, 0x02, 0x01, param, crc};
//        sendResponse(response,8);
        break;
    }
    }
}


