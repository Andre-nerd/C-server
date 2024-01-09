#include "const.h"

void recognize(struct command_package *input_data)
{
    printf("body size %d\n", input_data->length_body);
    for( int i = 0; i < HEADER_SIZE ; ++i )
    {
        printf("%d ", (char) input_data->header[i]);
    }
    for( int i = 0; i < input_data->length_body ; ++i )
    {
        printf("%d ", input_data->body[i]);
    }

};

void recognizeType(char *header, unsigned char body_size, char *body)
{
    printStructCommand(header, body_size, body);

}

void printStructCommand(char *header, unsigned char body_size, char *body)
{
    printf("new command:\n");
    for( int i = 0; i < HEADER_SIZE ; ++i )
    {
        printf("%d ", (char) header[i]);
    }
    printf("  ");
    for( int i = 0; i < body_size -1 ; ++i )
    {
        printf("%d ", body[i]);
    }
    printf("  ");
    printf("%d",body[body_size-1]);
    printf("\n");
}
