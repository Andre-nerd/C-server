#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "recognize_command.h"
#include "const.h"


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

    char head_buf[HEADER_SIZE];
    memset(head_buf, 0, sizeof(head_buf));

    SOCKET client_socket;
    SOCKADDR_IN client_addr;
    int client_addr_size = sizeof(client_addr);

    while(client_socket = accept(s, &client_addr, &client_addr_size))
    {
        printf("connect OK\n");
        while(1)
        {
            recv(client_socket, head_buf, sizeof(head_buf), 0);

            unsigned char body_size = head_buf[3] + 1;
            char* body_buf = (char*) malloc(body_size);
            if(body_buf != NULL)
            {
                recv(client_socket, body_buf, sizeof(body_buf), 0);

                STRUCT_COMMAND input_data;
                for(int i = 0; i < HEADER_SIZE; ++i)
                {
                    input_data.header[i] = head_buf[i];
                    printf("%d", input_data.header[i]);
                }

                for(int i = 0; i < body_size; ++i)
                {
                    input_data.body[i] = body_buf[i];
                    printf("%d", input_data.body[i]);
                }
                printf("\n");
                recognize(&input_data);
//            recognizeType(head_buf, body_buf);

                free(body_buf);
                printf("\n");

                char nm[4] =  {65,66,67,68};
                send(client_socket, nm, sizeof(nm), 0);
            }
        }
    }


    closesocket(s);
    return 0;
}
