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
