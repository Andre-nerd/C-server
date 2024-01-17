#ifndef COMMAND_MODULE_TELEMETRY_H_INCLUDED
#define COMMAND_MODULE_TELEMETRY_H_INCLUDED

void handlerModuleTelemetryCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int));

#endif // COMMAND_MODULE_TELEMETRY_H_INCLUDED
