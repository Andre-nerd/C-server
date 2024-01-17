#include "const.h"
#include "common_utils.h"

char setParamModuleTelemerty(char param)
{
    //Команда настраивает частоту регулярных сообщений телеметрии модуля
    // 0 - прислать один раз или выключить отправку
    // 1 - 1Гц, 2 - 2 Гц, 3 - 5 Гц, 4 - 10 Гц, 5 - 20 Гц.
    // Возвращает 0 или 0х10 - некорректная частота
    return 0;
}

char getParamModuleTelemerty()
{
    //Получаем действующию частоту регулярных сообщений телеметрии модуля
    // 0 - Отправка отключена
    // 1 - 1Гц, 2 - 2 Гц, 3 - 5 Гц, 4 - 10 Гц, 5 - 20 Гц.

    return 0x03;
}
// Команда 0х02
void handlerModuleTelemetryCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerModuleTelemetryCommand working\n ");

    switch(input_data->header[1])// Смотрим спецификатор
    {
    case 0: //Команда на установку параметров
    {

        char param = input_data->body[0];
        char status = setParamModuleTelemerty(param);
        char body[5] = {36, 0x02, 0x04, 0x01,status};
        char crc = crcCalc(body, 5);
        char response[6] = {36, 0x02, 0x04, 0x01,status,crc};
        sendResponse(response,6);
        break;
    }


    case 1: //Запрос параметра
    {
        char param = getParamModuleTelemerty();
        char body[6] = {36, 0x03, 0x04, 0x02, 0x01, param};
        char crc = crcCalc(body, 6);
        char response[7] = {36, 0x03, 0x04, 0x02, 0x01, param, crc};
        sendResponse(response,7);
        break;
    }
    }
}
