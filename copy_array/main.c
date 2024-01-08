#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fun1.h"

void* append(short* data, size_t *length, size_t *capacity, short value){
    if(*length >= *capacity){
        short *ar = malloc(sizeof(short) * 2 **capacity);
        if(ar == NULL)
            return data;

        (*capacity) *=2;
        /*
        for(int i=0; i<*length; ++i){
            ar[i] = data[i];
        }
        */
        memcpy(ar,data, *length * sizeof(short));
        free(data);
        data = ar;
    }
        data[*length] = value;
        (*length)++;
        return data;
}

int main(void){
    size_t capacity = 10;
    size_t length = 0;

    short *data = malloc(sizeof(short) * capacity);
    for(int i = 0; i < 11; ++i){
        data = append(data, &length, &capacity, (short) i);
    }
    printf("capacity = %u, length = %u\n", capacity, length);

    for(int i = 0; i <length; ++i){
        printf("%d", data[i]);
    }

    return 0;
}


