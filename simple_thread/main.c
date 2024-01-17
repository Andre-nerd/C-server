#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

HANDLE hThread;

int sleeping_time = 1000;
int thread_finish = 0;

void prn ()
{
    printf("Thread working...| Sleep %d\n", sleeping_time);
}

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
    do
    {
        prn();
        Sleep(sleeping_time);
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


int main()
{
    int input_console = 0;
    do
    {
        printf("Next command: 0 - Off, 1..5 - frequency, 99 - exit\n");
        scanf("%d",&input_console);
        switch(input_console)
        {
        case 0:
        {
            thread_finish = 1;
            CloseHandle( hThread );
            hThread = NULL;
            continue;
        }

        case 1:
        {
            thread_finish = 0;
            sleeping_time = 1000;
            break;
        }
        case 2:
        {
            thread_finish = 0;
            sleeping_time = 500;
            break;
        }
        case 3:
        {
            thread_finish = 0;
            sleeping_time = 200;
            break;
        }
        case 4:
        {
            thread_finish = 0;
            sleeping_time = 100;
            break;
        }
        case 5:
        {
            thread_finish = 0;
            sleeping_time = 50;
            break;
        }
        }


        if(hThread == NULL && input_console != 0)
        {
            createRegularThread();
        }

        printf("After CreateThread | thread = %d\n",hThread);

    }
    while(input_console != 99);
    CloseHandle( hThread );

}
