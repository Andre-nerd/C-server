#include "const.h"\
#include "on_off_command.h"

void recognize_command(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("recognize_command fun working\n");
    STRUCT_RESPONSE* response;
    printStructCommand(input_data->header, input_data->body);

    switch(input_data->header[2])
    {
    case on_off_command:
    {
        handlerOnOffCommand(input_data, sendResponse);
        break;
    }
    };



};


