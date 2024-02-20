#include "const.h"
#include "common_utils.h"

char setSystemCoordinates(char* body)
{
    systemCoordinates = *body;
    return 0;
}


// Команда 0х09
void handlerSystemCoordinatestCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerSystemCoordinatestCommand working\n ");

    switch(input_data->header[1])// Смотрим спецификатор
    {
    case 0: //Команда на установку параметров
    {
        char status = setSystemCoordinates(input_data->body);

        char body[6] = {36, 0x02, 0x09, 0x00, 0x01,status};
        char crc = crcCalc(body, 6);
        char response[7] = {36, 0x02, 0x05, 0x00, 0x02,status,crc};
        sendResponse(response,7);
        break;
    }
    }
}


