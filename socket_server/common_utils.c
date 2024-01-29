#include "const.h"

STRUCT_COMMAND getStructCommand(char *head_buf, char *body_buf)
{
    STRUCT_COMMAND output_data;
    for(int i = 0; i < HEADER_SIZE; ++i)
    {
        output_data.header[i] = head_buf[i];
    }

    for(int i = 0; i < head_buf[4]+1; ++i)
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
    for( int i = 0; i < header[4] ; ++i )
    {
        printf("%d ", body[i]);
    }
    printf("  ");
    printf("%d",body[header[4]]);
    printf("\n");
}
void printCommandByBytes(unsigned char *body, int length_body)
{
    for( int i = 0; i < HEADER_SIZE ; ++i )
    {
        printf("%d ", (char) body[i]);
    }
    printf("  ");
    for( int i = HEADER_SIZE; i < length_body ; ++i )
    {
        printf("%d ", body[i]);
    }
    printf("\n");
}

//   Функция возвращает контрольную сумму CRC8 (XOR) данных в буффере buf
//    длинной len
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

void get_bin_value(unsigned char v){
  for (int i = 0; i < 8; i++) {
    printf("%c", (v & 0x80) ? '1' : '0');
    v <<= 1;
  }
  printf("\n");
  return 0;
}
