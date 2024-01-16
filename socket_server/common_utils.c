#include "const.h"

STRUCT_COMMAND getStructCommand(char *head_buf, char *body_buf)
{
    STRUCT_COMMAND output_data;
    for(int i = 0; i < HEADER_SIZE; ++i)
    {
        output_data.header[i] = head_buf[i];
    }

    for(int i = 0; i < head_buf[3]+1; ++i)
    {
        output_data.body[i] = body_buf[i];
    }
    return output_data;
}

void printStructCommand(char *header, char *body)
{
    printf("new command:\n");
    for( int i = 0; i < HEADER_SIZE ; ++i )
    {
        printf("%d ", (char) header[i]);
    }
    printf("  ");
    for( int i = 0; i < header[3] ; ++i )
    {
        printf("%d ", body[i]);
    }
    printf("  ");
    printf("%d",body[header[3]]);
    printf("\n");
}

//   ������� ���������� ����������� ����� CRC8 (XOR) ������ � ������� buf
//    ������� len
//
unsigned char crcCalc(unsigned char *buf, int len)
{
    unsigned char *ubyte = (unsigned char *)buf;

    unsigned char crc = *ubyte;
    ubyte++;
    int i = 0;
    while (++i < len)
    {
        crc ^= *ubyte;
        ubyte++;
    }

    return crc;
}
