#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "recognize_command.h"
#include "const.h"
#include "common_utils.h"

SOCKET client_socket;
fd_set Fds;
struct timeval stv = {0, TIME_WAIT_SOCKET};

void sendResponse(char* response, int length_response )
{
    send(client_socket, response, length_response, 0);
}

int main()
{

connect:
    navigation_frequency  = 0;
    telemetry_frequency = 0;
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



    client_socket = accept(s, &client_addr, &client_addr_size);

    printf("The client has connected\n");
    clock_t telemetry_start = clock(),navigation_start = clock(), telemetry_diff, navigation_diff;
    imitation_cycle_navigation = 0; //Счетчик для имитации изменения координат. Только тестовый режим
    imitation_cycle_telemetry = 0; //Счетчик для имитации изменения телеметрии модуля. Только тестовый режим

    while(1)
    {
        if(telemetry_frequency != 0) // Send regular telemetry module message
        {
            telemetry_diff = clock() - telemetry_start;
            int msec_telemetry = telemetry_diff * 1000 / CLOCKS_PER_SEC ;
            if(msec_telemetry >= 1000 / telemetry_frequency)
            {
                sendRegularTelemetryMessage(sendResponse);
                telemetry_start = clock();
                imitation_cycle_telemetry++;
                if (imitation_cycle_telemetry > 4) imitation_cycle_telemetry = 0;
            }
        }

        if(navigation_frequency != 0) // Send regular navigation message
        {
            navigation_diff = clock() - navigation_start;
            int msec_navigation = navigation_diff * 1000 / CLOCKS_PER_SEC ;
            if(msec_navigation >= 1000 / navigation_frequency)
            {
                sendRegularNavigationMessage(sendResponse);
                navigation_start = clock();
                imitation_cycle_navigation++;
                if (imitation_cycle_navigation > 4) imitation_cycle_navigation = 0;
            }
        }



        FD_ZERO(&Fds);
        FD_SET(client_socket, &Fds);
        if (select(client_socket + 1,&Fds, NULL, NULL, &stv) > 0)
        {
            int response = recv(client_socket, head_buf, sizeof(head_buf), 0);
            printf("response = %d\n", response);
            if(response == -1)
            {
                break;
            }

            unsigned char body_size = head_buf[4] + 1;
            char* body_buf = (char*) malloc(body_size);
            if(body_buf != NULL)
            {
                recv(client_socket, body_buf, body_size, 0);
                STRUCT_COMMAND input_data = getStructCommand(head_buf, body_buf);

                recognize_command(&input_data, sendResponse);
                free(body_buf);
            }

        }

    }


    closesocket(s);
    goto connect;
    return 0;
}
