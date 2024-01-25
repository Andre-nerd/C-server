#include "const.h"
#include "common_utils.h"

char dCharge = 0;
void sendRegularTelemetryMessage(void (*sendResponse)(char*, int))
{
    short batteryVoltage;
    short batteryCurrent;
    short weightRTK;
    short weightPPP;
    char batteryChargeLevel;
    char setting;
    char lastAmendmentTimeRTK;
    char lastAmendmentTimePPP;

    batteryVoltage = 7;
    batteryCurrent = 2;
    weightRTK = 9801;
    weightPPP = 37708;
    batteryChargeLevel = 1 + dCharge;
    dCharge++;
    if(dCharge == 98) dCharge = 1;
    char _chargeLevel = batteryChargeLevel;
    _chargeLevel |= (1 << 7);

    setting = 0;
    lastAmendmentTimeRTK = 134;
    lastAmendmentTimePPP = 12;

    char batteryVoltage_bytes[sizeof(short)];
    memcpy(batteryVoltage_bytes, &batteryVoltage, sizeof(short));
    char batteryCurrent_bytes[sizeof(short)];
    memcpy(batteryCurrent_bytes, &batteryCurrent, sizeof(short));
    char weightRTK_bytes[sizeof(short)];
    memcpy(weightRTK_bytes, &weightRTK, sizeof(short));
    char weightPPP_bytes[sizeof(short)];
    memcpy(weightPPP_bytes, &weightPPP, sizeof(short));

    char body[18] = {36,0x04,0x04,0x00,0x0C};
    for(int i=0; i < 2; ++i)
    {
        body[i+5] = batteryVoltage_bytes[i];
        body[i+7] = batteryCurrent_bytes[i];
        body[i+9] = weightRTK_bytes[i];
        body[i+11] = weightPPP_bytes[i];
    }
    body[13] = _chargeLevel;
    body[14] = setting;
    body[15] = lastAmendmentTimeRTK;
    body[16] = lastAmendmentTimePPP;


    char crc = crcCalc(body,17);
    body[17] = crc;
    printf("send Regular Telemetry message\n");
    printCommandByBytes(body, sizeof(body));
    sendResponse(body,18);
}
char setParamModuleTelemerty(char param)
{
    //Команда настраивает частоту регулярных сообщений телеметрии модуля
    // 0 - прислать один раз или выключить отправку
    // 1 - 1Гц, 2 - 2 Гц, 3 - 5 Гц, 4 - 10 Гц, 5 - 20 Гц.
    // Возвращает 0 или 0х10 - некорректная частота
    telemetry_frequency = param;
    return 0;
}

char getParamModuleTelemerty()
{
    //Получаем действующию частоту регулярных сообщений телеметрии модуля
    // 0 - Отправка отключена
    // 1 - 1Гц, 2 - 2 Гц, 3 - 5 Гц, 4 - 10 Гц, 5 - 20 Гц.

    return telemetry_frequency;
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
        char body[6] = {36, 0x02, 0x04, 0x00,0x01,status};
        char crc = crcCalc(body, 6);
        char response[7] = {36, 0x02, 0x04, 0x00,0x01,status,crc};
        sendResponse(response,7);
        break;
    }


    case 1: //Запрос параметра
    {
        char param = getParamModuleTelemerty();
        char body[7] = {36, 0x03, 0x04, 0x00,0x02, 0x00, param};
        char crc = crcCalc(body, 7);
        char response[8] = {36, 0x03, 0x04, 0x00,0x02, 0x00, param, crc};
        sendResponse(response,8);
        break;
    }
    }
}
