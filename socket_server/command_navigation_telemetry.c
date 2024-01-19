#include "const.h"
#include "common_utils.h"


void sendRegularNavigationMessage(void (*sendResponse)(char*, int))
{
    float latitude;
    float longitude;
    float altitude;
    float precision;
    char valid;
    char devices;
    char modeGNSS;
    char satellitesAll;
    char satellitesSolution;
    char stantionLSNALL;
    char stantionLSNSolution;
    char iBeaconALL;
    char iBeaconSolution;
    char wifiRTTALL;
    char wifiRTTSolution;

    switch(imitation_cycle_navigation)// Только для имитации изменения координат в тестовом режиме
    {
    case 0:
    {
        latitude = 55.3786;
        longitude = 37.4532;
        altitude = 123.45;
        precision = 4.52;
        break;
    }
    case 1:
    {
        latitude = 55.378673;
        longitude = 37.453298;
        altitude = 120.45;
        precision = 6.72;
        break;
    }
    case 2:
    {
        latitude = 55.378665;
        longitude = 37.453274;
        altitude = 121.01;
        precision = 5.721;
        break;
    }
    case 3:
    {
        latitude = 55.378699;
        longitude = 37.453300;
        altitude = 123.12;
        precision = 3.22;
        break;
    }
    case 4:
    {
        latitude = 55.3787001;
        longitude = 37.4532021;
        altitude = 123.76;
        precision = 4.89;
        break;
    }
    };


    valid = 1;
    devices = 7;
    modeGNSS = 1;
    satellitesAll = 11;
    satellitesSolution = 8;
    stantionLSNALL = 7;
    stantionLSNSolution = 4;
    iBeaconALL = 8;
    iBeaconSolution = 4;
    wifiRTTALL = 12;
    wifiRTTSolution = 9;

    char latitude_bytes[sizeof(float)];
    memcpy(latitude_bytes, &latitude, sizeof(float));
    char longitude_bytes[sizeof(float)];
    memcpy(longitude_bytes, &longitude, sizeof(float));
    char altitude_bytes[sizeof(float)];
    memcpy(altitude_bytes, &altitude, sizeof(float));
    char precision_bytes[sizeof(float)];
    memcpy(precision_bytes, &precision, sizeof(float));

    char body[32] = {36,0x04,0x03,0x1B};
    for(int i=0; i < 4; ++i)
    {
        body[i+4] = latitude_bytes[i];
        body[i+8] = longitude_bytes[i];
        body[i+12] = altitude_bytes[i];
        body[i+16] = precision_bytes[i];
    }
    body[20] = valid;
    body[21] = devices;
    body[22] = modeGNSS;
    body[23] = satellitesAll;
    body[24] = satellitesSolution;
    body[25] = stantionLSNALL;
    body[26] = stantionLSNSolution;
    body[27] = iBeaconALL;
    body[28] = iBeaconSolution;
    body[29] = wifiRTTALL;
    body[30] = wifiRTTSolution;

    char crc = crcCalc(body,31);
    body[31] = crc;
    printf("send Regular Navigation message\n");
    printCommandByBytes(body, sizeof(body));
    sendResponse(body,32);
}

char setParamNavigationTelemerty(char param)
{
    //Команда настраивает частоту регулярных сообщений навигационной телеметрии
    // 0 - прислать один раз или выключить отправку
    // 1 - 1Гц, 2 - 2 Гц, 3 - 5 Гц, 4 - 10 Гц, 5 - 20 Гц.
    // Возвращает 0 или 0х10 - некорректная частота
    navigation_frequency = param;
    return 0;
}

char getParamNavigationTelemerty()
{
    //Получаем действующию частоту регулярных сообщений навигационной телеметрии
    // 0 - Отправка отключена
    // 1 - 1Гц, 2 - 2 Гц, 3 - 5 Гц, 4 - 10 Гц, 5 - 20 Гц.

    return navigation_frequency;
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
