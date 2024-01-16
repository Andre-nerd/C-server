#include "const.h"
#include "common_utils.h"

char setAmendment(char amendment, char mask)
{
    //Устанавливаем подписки на поправки. Если успешно 0 иначе 0х10 некорректный выбор устройств
    return 0;
}

char getAmendment()
{
    //Получаем действующие подписки

    return 0x07;
}
// Команда 0х01
void handlerAmendmentCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerAmendmentCommand working\n ");

    switch(input_data->header[1])// Смотрим спецификатор
    {
    case 0: //Команда на установку параметров
    {
        char mask = input_data->body[0];
        char param = input_data->body[1];
        char status = setAmendment(param, mask);
        char body[5] = {36, 0x02, 0x02, 0x01,status};
        char crc = crcCalc(body, 5);
        char response[6] = {36, 0x02, 0x02, 0x01,status,crc};
        sendResponse(response,6);
        break;
    }


    case 1: //Запрос параметра
    {
        char param = getAmendment();
        char body[6] = {36, 0x03, 0x02, 0x02, 0x01, param};
        char crc = crcCalc(body, 6);
        char response[7] = {36, 0x03, 0x02, 0x02, 0x01, param, crc};
        sendResponse(response,7);
        break;
    }
    }
}


