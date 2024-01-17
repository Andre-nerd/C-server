#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define HEADER_SIZE 4


SOCKET client_socket;
int sleeping_time = 1000;

void sendResponse(char* response, int length_response )
{
    send(client_socket, response, length_response, 0);
}
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
    while(1){
        printf("Thread working...| Sleep %d\n", sleeping_time);
        Sleep(sleeping_time);
    }

//    char szMsg[80];
//
//    wsprintf(szMsg, "Parameter = %d", *(DWORD*)lpParam);
//
//    MessageBox( NULL, szMsg, " ThreadFunc", MB_OK );

    return 0;

}

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

    SOCKADDR_IN client_addr;
    int client_addr_size = sizeof(client_addr);

    while(client_socket = accept(s, &client_addr, &client_addr_size))
    {
        printf("The client has connected\n");
//        while(1)
//        {
//            recv(client_socket, head_buf, sizeof(head_buf), 0);
//
//            unsigned char body_size = head_buf[3] + 1;
//            char* body_buf = (char*) malloc(body_size);
//            if(body_buf != NULL)
//            {
//                recv(client_socket, body_buf, sizeof(body_buf), 0);
////                STRUCT_COMMAND input_data = getStructCommand(head_buf, body_buf);
////                recognize_command(&input_data, sendResponse);
//                free(body_buf);
//            }
//        }
        DWORD dwThreadId, dwThrdParam = 1;

        HANDLE hThread;

        char szMsg[80];
        hThread = CreateThread(

                      NULL,         // атрибуты безопасности по умолчанию

                      0,            // размер стека используется по умолчанию

                      ThreadFunc,   // функция потока

                      &dwThrdParam, // аргумент функции потока

                      0,            // флажки создания используются по умолчанию

                      &dwThreadId); // возвращает идентификатор потока

// При успешном завершении проверяет возвращаемое значение.
        printf("Set sleep time");
        scanf("%d", &sleeping_time);
//        if (hThread == NULL)
//
//        {
//            wsprintf( szMsg, "CreateThread failed." );
//            MessageBox( NULL, szMsg, "main", MB_OK );
//        }
//        else
//        {
//            _getch();
//            CloseHandle( hThread );
//        }

    }


    closesocket(s);
    return 0;
}
