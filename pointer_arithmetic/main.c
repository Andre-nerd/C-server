#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[4] = {1,1,1,1};
    char b[2] = {2,2};
    char c[3] = {3,3,3};

    concat(a,b);


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
