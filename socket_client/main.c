#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int sendMessage(SOCKET s, short* data, int capacity){
    send(s, data, capacity, 0);
}

int recieveMessage(SOCKET s){
    char header[4];
    int length = sizeof(header);
    memset(header, 0, length);
    recv(s, header, length, 0);
    printf("header: text/byte\n");
    puts(header);
    for(int i = 0; i < length; ++i){
        printf("%d", header[i]);
    }
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
        while(cnt != 0){
        Sleep(500);
        cnt = connect(s, &sa, sizeof(sa) );
        printf("connect res: %d\n", cnt);
        }

        char command = 's';
        do{
            int mas[] = {34,22,78,1};
            sendMessage(s,mas,sizeof(mas));
            Sleep(500);

            recieveMessage(s);

            printf("command: ");
            scanf("%c", &command);
            printf("input %d\n", command);

        }while(command != 'q');

    closesocket(s);
    return 0;
}
