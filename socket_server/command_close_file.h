#ifndef COMMAND_CLOSE_FILE_H_INCLUDED
#define COMMAND_CLOSE_FILE_H_INCLUDED

void handlerCloseFileWriteCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int));

#endif // COMMAND_CLOSE_FILE_H_INCLUDED
