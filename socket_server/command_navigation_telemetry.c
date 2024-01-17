#include "const.h"
#include "common_utils.h"



char setParamNavigationTelemerty(char param)
{
    //Команда настраивает частоту регулярных сообщений навигационной телеметрии
    // 0 - прислать один раз или выключить отправку
    // 1 - 1Гц, 2 - 2 Гц, 3 - 5 Гц, 4 - 10 Гц, 5 - 20 Гц.
    // Возвращает 0 или 0х10 - некорректная частота
    return 0;
}

char getParamNavigationTelemerty()
{
    //Получаем действующию частоту регулярных сообщений навигационной телеметрии
    // 0 - Отправка отключена
    // 1 - 1Гц, 2 - 2 Гц, 3 - 5 Гц, 4 - 10 Гц, 5 - 20 Гц.

    return 0x05;
}
// Команда 0х02
void handlerNavigationTelemetryCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerNavigationTelemetryCommand working\n ");

    switch(input_data->header[1])// Смотрим спецификатор
    {
    case 0: //Команда на установку параметров
    {

        char param = input_data->body[0];
        char status = setParamNavigationTelemerty(param);
        char body[5] = {36, 0x02, 0x03, 0x01,status};
        char crc = crcCalc(body, 5);
        char response[6] = {36, 0x02, 0x03, 0x01,status,crc};
        sendResponse(response,6);
        break;
    }


    case 1: //Запрос параметра
    {
        char param = getParamNavigationTelemerty();
        char body[6] = {36, 0x03, 0x03, 0x02, 0x01, param};
        char crc = crcCalc(body, 6);
        char response[7] = {36, 0x03, 0x03, 0x02, 0x01, param, crc};
        sendResponse(response,7);
        break;
    }
    }
}









//
//    float float_value = 43.5678;
//    char float_bytes[sizeof(float)];
//    memcpy(float_bytes, &float_value, sizeof(float));
