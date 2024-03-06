#include "const.h"

getStructCommand(char *head_buf, char *body_buf, STRUCT_COMMAND *output_data)
{
    for(int i = 0; i < HEADER_SIZE; ++i)
    {
        output_data->header[i] = head_buf[i];
    }

    for(int i = 0; i < head_buf[3]+1; ++i)
    {
        output_data->body[i] = body_buf[i];
    }
    printf("----------------------get struct command-----------------------------\n");
    printf("----------------------source-----------------------------\n");
    printStructCommand(&head_buf, &body_buf );
    printf("----------------------output data-----------------------------\n");
    printStructCommand(&output_data->header, &output_data->body );
    return output_data;
}

void printStructCommand(char *header, char *body)
{
//    printf("new command:\n");
    for( int i = 0; i < HEADER_SIZE ; ++i )
    {
        printf("%d ", (char) header[i]);
    }
    printf(" length body: %d  ", header[3] );
    for( int i = 0; i < header[3] ; ++i )
    {
        printf("%d ", body[i]);
    }
    printf("  ");
    printf("%d",body[header[3]]);
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
