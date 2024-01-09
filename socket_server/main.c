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

    int header_size = 4;

    SOCKADDR_IN sa;
        memset(&sa, 0, sizeof(sa) );
        sa.sin_family =  AF_INET;
        sa.sin_port = htons(9999);

        bind(s, &sa, sizeof(sa));
        listen(s, 100);

        char head_buf[header_size];
        memset(head_buf, 0, sizeof(head_buf));

        SOCKET client_socket;
        SOCKADDR_IN client_addr;
        int client_addr_size = sizeof(client_addr);

        while(client_socket = accept(s, &client_addr, &client_addr_size)){
            printf("connect OK\n");
            while(1){
            recv(client_socket, head_buf, sizeof(head_buf), 0);

            int body_size = head_buf[3] + 1;
            char* body_buf = (char*) malloc(body_size);
            recv(client_socket, body_buf, sizeof(body_buf), 0);

            for( int i = 0; i < header_size; ++i ){
                    printf("%d ", head_buf[i]);
                }
            for( int i = 0; i < body_size; ++i ){
                    printf("%d ", body_buf[i]);
                }
            printf("\n");


//            while(recv(client_socket, buf, sizeof(buf), 0) > 0 ){
//                for( int i = 0; i < header_size; ++i ){
//                    printf("%d ", buf[i]);
//                }
//                printf("\n");
//
                char nm[4] =  {65,66,67,68};
                send(client_socket, nm, sizeof(nm), 0);
//            }
            }
        }


    closesocket(s);
    return 0;
}
