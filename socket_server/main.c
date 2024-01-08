#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main()
{
    printf("Server launced: v 3.0\n ");
    WSADATA ws;
    WSAStartup(MAKEWORD(2,2), &ws);

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM,0);

    SOCKADDR_IN sa;
        memset(&sa, 0, sizeof(sa) );
        sa.sin_family =  AF_INET;
        sa.sin_port = htons(9999);

        bind(s, &sa, sizeof(sa));
        listen(s, 100);

        int buf[5];
        memset(buf, 0, sizeof(buf));

        SOCKET client_socket;
        SOCKADDR_IN client_addr;
        int client_addr_size = sizeof(client_addr);

        while(client_socket = accept(s, &client_addr, &client_addr_size)){
            printf("connect OK\n");

            while(recv(client_socket, buf, sizeof(buf), 0) > 0 ){
                for( int i = 0; i < 5; ++i ){
                    printf("%d ", buf[i]);
                }
                printf("\n");

                char nm[4] =  {65,66,67,68};
                send(client_socket, nm, sizeof(nm), 0);
            }
        }


    closesocket(s);
    return 0;
}
