#include "const.h"
#include "common_utils.h"

char closeFileByDescriptor(char descriptor){
    // Закрываем файл по дескриптору

    return 0x00;
}

// Команда 0х06
void handlerCloseFileWriteCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerCloseFileWriteCommand working\n ");
    // Закрываем файл по дескриптору
    char descriptor = input_data->body[0];
    char status = closeFileByDescriptor(descriptor);

    //Формируем короткий ответ. По протоколу существует только ответ на команду, спецификатор 0х02
    unsigned char response[6] = {36,0x02,0x06,0x01,status};
    unsigned char crc = crcCalc(response, 5);
    response[5] = crc;
    sendResponse(response,6);

}


