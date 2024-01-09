#include "const.h"

void recognize(struct command_package *input_data)
{
//    printf("header %d  body %d", input_data->header, input_data->body);
    printStructCommand(input_data->header, input_data->header[3], input_data->body);

};

void recognizeType(char *header, char *body)
{
    printStructCommand(header, body);
    switch(header[2])
    {
    case on_off:
        printf("type: %d", on_off );

    }
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