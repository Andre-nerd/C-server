#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int sendMessage(SOCKET s, short* data, int capacity)
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
    char header[4];
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
    char* body_buf = (char*) malloc(body_size);
    memset(body_buf, 0, body_size);
    recv(s, body_buf, body_size, 0);
    for(int i = 0; i < body_size; ++i)
    {
        printf("%d ", body_buf[i]);
    }
    free(body_buf);

    printf("\n");
}

int main()
{
    printf("Client launced: v 1.0\n ");
    WSADATA ws;
    WSAStartup(MAKEWORD(2,2), &ws);

    SOCKET s;
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

    char command = 0;
    printf("command 0x00:- On/Off");
    printf("command 0x01: 1-Get param 0x01  11 - Send command 0x01\n");
    printf("command 0x02: 2-Get param 0x02  22 - Send command 0x02\n");
    printf("command 0x03: 3-Get param 0x03  33 - Send command 0x03\n");
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
            unsigned char g[5] = {36,0,0x03,0x01,5};
            char crc = crcCalc(g, 5);
            char mas[6] = {36,0,0x03,0x01,5,crc};;
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);
            break;
        }
        }


        recieveMessage(s);

    }
    while(command != 999);

    closesocket(s);
    return 0;
}


