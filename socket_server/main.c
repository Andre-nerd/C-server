#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <unistd.h>
#include <fcntl.h>
#include "recognize_command.h"
#include "const.h"
#include "common_utils.h"

SOCKET client_socket;
fd_set Fds;
struct timeval stv = {0, 250000};

void sendResponse(char* response, int length_response )
{
    send(client_socket, response, length_response, 0);
}

int main()
{
    navigation_frequency  = 0;
    navigation_frequency = 0;
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

    SOCKADDR_IN client_addr;
    int client_addr_size = sizeof(client_addr);

    while(client_socket = accept(s, &client_addr, &client_addr_size))
    {
        printf("The client has connected\n");
        while(1)
        {
            printf("navigation_frequency %d\n", navigation_frequency);
            printf("telemetry module_frequency %d\n", telemetry_frequency);

            FD_ZERO(&Fds);
            FD_SET(client_socket, &Fds);
            if (select(client_socket + 1,&Fds, NULL, NULL, &stv) > 0)
            {
                recv(client_socket, head_buf, sizeof(head_buf), 0);

                unsigned char body_size = head_buf[3] + 1;
                char* body_buf = (char*) malloc(body_size);
                if(body_buf != NULL)
                {
                    recv(client_socket, body_buf, sizeof(body_buf), 0);
                    STRUCT_COMMAND input_data = getStructCommand(head_buf, body_buf);
                    recognize_command(&input_data, sendResponse);
                    free(body_buf);
                }

            }
        }
    }


    closesocket(s);
    return 0;
}
