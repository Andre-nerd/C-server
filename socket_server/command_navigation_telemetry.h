#ifndef COMMAND_NAVIGATION_TELEMETRY_H_INCLUDED
#define COMMAND_NAVIGATION_TELEMETRY_H_INCLUDED

void handlerNavigationTelemetryCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int));
void sendRegularNavigationMessage(void (*sendResponse)(char*, int));


#endif // COMMAND_NAVIGATION_TELEMETRY_H_INCLUDED
