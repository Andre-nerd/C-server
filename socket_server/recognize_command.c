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
    case devices_for_solution:
    {
        handlerDevicesForSolutionCommand(input_data, sendResponse);
        break;
    }
    case amendment_manage:
    {
        handlerAmendmentCommand(input_data, sendResponse);
        break;
    }
    case navigation_telemetry:
    {
        handlerNavigationTelemetryCommand(input_data, sendResponse);
        break;
    }
        case module_telemetry:
    {
        handlerModuleTelemetryCommand(input_data, sendResponse);
        break;
    }
    };



};


