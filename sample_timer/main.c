#include <stdio.h>
#include <time.h>

int finish = 0;
int frequency = 1;

void regularMessageTimer()
{
    clock_t start = clock(), diff;
    do
    {
        diff = clock() - start;
        int msec1 = diff * 1000 / CLOCKS_PER_SEC ;
        if(msec1 >= 1000 / frequency)
        {
            printf("Time taken 1 seconds");
            start = clock();
        }
    }
    while(finish == 0);
}

int main()
{

    regularMessageTimer();
    printf("set frequnecy\n");


    return 0;
}
