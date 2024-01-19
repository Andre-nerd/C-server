#include "const.h"
#include "common_utils.h"


// Команда 0х07
void handlerRequestParamModuleCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerRequestParamModuleCommand working\n ");

    //Формируем короткий ответ. По протоколу существует только ответ на запрос параметра, спецификатор 0х03
    unsigned char status = 0;
    unsigned char response[11] = {36,0x03,0x07,0x06,status,components_for_recording, settingAmendment, navigation_frequency,telemetry_frequency };
    unsigned char crc = crcCalc(response, 10);
    response[10] = crc;
    sendResponse(response,11);

}
