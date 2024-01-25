#include "const.h"
#include "common_utils.h"


// Команда 0х07
void handlerRequestParamModuleCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerRequestParamModuleCommand working\n ");

    //Формируем короткий ответ. По протоколу существует только ответ на запрос параметра, спецификатор 0х03
    int id = 770409012;
    char id_bytes[sizeof(int)];
    memcpy(id_bytes, &id, sizeof(int));
    unsigned char status = 0;
    unsigned char response[15] = {36,0x03,0x07,0x00,0x06,status,components_for_recording,
     settingAmendment, navigation_frequency,telemetry_frequency,
     id_bytes[0], id_bytes[1], id_bytes[2], id_bytes[3]
     };
    unsigned char crc = crcCalc(response, 14);
    response[14] = crc;
    sendResponse(response,15);

}
