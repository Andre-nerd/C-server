#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define TIME_WAIT_SOCKET 200000

SOCKET s;
fd_set Fds;
struct timeval stv = {0, TIME_WAIT_SOCKET};
HANDLE hThread;
int thread_finish = 0;


DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
    do
    {
        FD_ZERO(&Fds);
        FD_SET(s, &Fds);
        if (select(s + 1,&Fds, NULL, NULL, &stv) > 0)
        {
            recieveMessage(s);
        }
    }
    while(thread_finish != 1);
    return 0;
}

void createRegularThread()
{
    DWORD dwThreadId, dwThrdParam = 1;

    hThread = CreateThread(

                  NULL,         // атрибуты безопасности по умолчанию

                  0,            // размер стека используется по умолчанию

                  ThreadFunc,   // функция потока

                  &dwThrdParam, // аргумент функции потока

                  0,            // флажки создания используются по умолчанию

                  &dwThreadId); // возвращает идентификатор потока

// При успешном завершении проверяет возвращаемое значение.
    if (hThread == NULL)

    {
        printf("CreateThread failed.\n" );
    }
}

int sendMessage(SOCKET s, unsigned short* data, int capacity)
{
    send(s, data, capacity, 0);
}
void showWhatCommandGetResponse(int command)
{
    switch(command)
    {
    case 0:
    {
        printf("Response by command ON/OFF\n");
        break;
    }
    case 1:
    {
        printf("Response by command Devices for Solution\n");
        break;
    }
    case 2:
    {
        printf("Response by command Amendment Manager\n");
        break;
    }
    case 3:
    {
        printf("Response by command Navigation Telemetry\n");
        break;
    }
    case 4:
    {
        printf("Response by command Module Telemetry\n");
        break;
    }
    case 5:
    {
        printf("Response by command Open File for record\n");
        break;
    }

    }
}


unsigned char crcCalc(unsigned char *buf, int len)
{
    unsigned char *ubyte = (unsigned char *)buf;

    unsigned char crc = *ubyte;
    ubyte++;
    int i = 0;
    while (++i < len)
    {
        crc ^= *ubyte;
        ubyte++;
    }

    return crc;
}

int recieveMessage(SOCKET s)
{
    unsigned char header[4];
    int length = sizeof(header);
    memset(header, 0, length);
    recv(s, header, length, 0);

    showWhatCommandGetResponse((int)header[2]);

    for(int i = 0; i < length; ++i)
    {
        printf("%d ", header[i]);
    }
    printf(" ");
    int body_size = header[3]+1;
    unsigned char* body_buf = (char*) malloc(body_size);
    memset(body_buf, 0, body_size);
    recv(s, body_buf, body_size, 0);
    for(int i = 0; i < body_size; ++i)
    {
        printf("%d ", body_buf[i]);
    }

    int length_without_crc = 4 + header[3];
    unsigned char* crc_buf = (char*) malloc(length_without_crc);
    for (int i = 0; i <4;++i){
        crc_buf[i] = header[i];
    };
    for(int i=0; i<length_without_crc-4;++i){
        crc_buf[i+4] = body_buf[i];
    };
    unsigned char crc = crcCalc(crc_buf, length_without_crc);
    if(crc == body_buf[header[3]]){
        printf("CRC is correct = %d\n",crc);
    } else {
        printf("! CRC is not correct = %d\n",crc);
    }
    free(crc_buf);
    free(body_buf);

    printf("\n");
}

int main()
{
    printf("Client launced: v 1.0\n ");
    WSADATA ws;
    WSAStartup(MAKEWORD(2,2), &ws);

    s = socket(AF_INET, SOCK_STREAM,0);

    SOCKADDR_IN sa;
    memset(&sa, 0, sizeof(sa) );
    sa.sin_family =  AF_INET;
    sa.sin_port = htons(9999);
    int cnt = -1;

    sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    while(cnt != 0)
    {
        Sleep(500);
        cnt = connect(s, &sa, sizeof(sa) );
        printf("connect res: %d\n", cnt);
    }
    createRegularThread();

    char command = 0;
    printf("command 0x00:- On/Off");
    printf("command 0x01: 1-Get param 0x01  11 - Send command 0x01\n");
    printf("command 0x02: 2-Get param 0x02  22 - Send command 0x02\n");
    printf("command 0x03: 3-Get param 0x03  33 - Send command 0x03\n");
    printf("command 0x04: 4-Get param 0x04  44 - Send command 0x04\n");
    printf("command 0x05: 5-Get param 0x05  55 - Send command 0x05\n");
    do
    {

        scanf("%d", &command);
        printf("input %d\n", command);
        switch(command)
        {
        case 0:
        {
            char mas[] = {36,0,0,1,1,78};
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 1:
        {
            unsigned char g[5] = {36,0x01,0x01,1,0x1E};
            char crc = crcCalc(g, 5);
            char mas[6] = {36,0x01,0x01,1,0x1E,crc};
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 11:
        {
            unsigned char g[5] = {36,0,0x01,1,0x1E};
            char crc = crcCalc(g, 5);
            char mas[6] = {36,0,0x01,1,0x1E,crc};
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 2:
        {
            unsigned char g[4] = {36,0x01,0x02,0};
            char crc = crcCalc(g, 4);
            char mas[5] = {36,0x01,0x02,1,crc};
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 22:
        {
            unsigned char g[6] = {36,0,0x02,0x02,7,7};
            char crc = crcCalc(g, 6);
            char mas[7] = {36,0,0x02,0x02,7,7,crc};;
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 3:
        {
            unsigned char g[4] = {36,0x01,0x03,0};
            char crc = crcCalc(g, 4);
            char mas[5] = {36,0x01,0x03,1,crc};
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 33:
        {
            char freq = 1;
            printf("Set Navigation Frequency (0..5) = ");
            scanf("%d",&freq);
            unsigned char g[5] = {36,0,0x03,0x01,freq};
            char crc = crcCalc(g, 5);
            char mas[6] = {36,0,0x03,0x01,freq,crc};;
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 4:
        {
            unsigned char g[4] = {36,0x01,0x04,0};
            char crc = crcCalc(g, 4);
            char mas[5] = {36,0x01,0x04,1,crc};
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 44:
        {
            char freq = 1;
            printf("Set Telemetry Module Frequency (0..5) = ");
            scanf("%d",&freq);
            unsigned char g[5] = {36,0,0x04,0x01,freq};
            char crc = crcCalc(g, 5);
            char mas[6] = {36,0,0x04,0x01,freq,crc};;
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 5:
        {
            unsigned char g[4] = {36,0x01,0x05,0};
            char crc = crcCalc(g, 4);
            char mas[5] = {36,0x01,0x05,0,crc};
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        case 55:
        {
            char record_component = 7;
            unsigned char file_name_current[9] = "exam_name";

            unsigned char mas[15] = {36,0,0x05,0xA,record_component};
            for(int i = 5; i < 14; i++){
                mas[i] = file_name_current[i-5];
            }
            char crc = crcCalc(mas, 14);
            mas[14] = crc;
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        }

    }
    while(command != 999);

    CloseHandle( hThread );
    closesocket(s);

    return 0;
}


