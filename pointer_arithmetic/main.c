#include <stdio.h>
#include <stdlib.h>

int main()
{
    float float_value = 43.5678;
    char float_bytes[sizeof(float)];
    memcpy(float_bytes, &float_value, sizeof(float));

    for(int i = 0; i <4; ++i)
    {
        get_bin_value(float_bytes[i]);

    }

    float* recovery = float_bytes;
    printf("%.4f", *recovery);

    return 0;
}

void get4BytesFromFloat(float value, char* arr)
{
    char* ptr = &value;
    arr[0] = *ptr;
    ptr++;
    arr[1] = *ptr;
    ptr++;
    arr[2] = *ptr;
    ptr++;
    arr[3] = *ptr;
}

void get_bin_value(unsigned char v)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%c", (v & 0x80) ? '1' : '0');
        v <<= 1;
    }
    printf("\n");
    return 0;
}
