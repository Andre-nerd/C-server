#ifndef ON_OFF_COMMAND_H_INCLUDED
#define ON_OFF_COMMAND_H_INCLUDED

void handlerOnOffCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int));

#endif // ON_OFF_COMMAND_H_INCLUDED
