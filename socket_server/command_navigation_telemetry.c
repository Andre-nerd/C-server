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
        satellitesAll = 11;
        satellitesSolution = 0;
        stantionLSNALL = 7;
        stantionLSNSolution = 0;
        iBeaconALL = 8;
        iBeaconSolution = 0;
        wifiRTTALL = 12;
        wifiRTTSolution = 0;
        break;
    }
    case 1:
    {
        latitude = 55.378673;
        longitude = 37.453298;
        altitude = 120.45;
        precision = 6.72;
        satellitesAll = 15;
        satellitesSolution = 0;
        stantionLSNALL = 9;
        stantionLSNSolution = 0;
        iBeaconALL = 8;
        iBeaconSolution = 4;
        wifiRTTALL = 19;
        wifiRTTSolution = 0;
        break;
    }
    case 2:
    {
        latitude = 55.378665;
        longitude = 37.453274;
        altitude = 121.01;
        precision = 5.721;
        satellitesAll = 11;
        satellitesSolution = 4;
        stantionLSNALL = 7;
        stantionLSNSolution = 0;
        iBeaconALL = 8;
        iBeaconSolution = 0;
        wifiRTTALL = 12;
        wifiRTTSolution = 0;
        break;
    }
    case 3:
    {
        latitude = 55.378699;
        longitude = 37.453300;
        altitude = 123.12;
        precision = 3.22;
        satellitesAll = 15;
        satellitesSolution = 4;
        stantionLSNALL = 9;
        stantionLSNSolution = 0;
        iBeaconALL = 8;
        iBeaconSolution = 0;
        wifiRTTALL = 19;
        wifiRTTSolution = 4;
        break;
    }
    case 4:
    {
        latitude = 55.3787001;
        longitude = 37.4532021;
        altitude = 123.76;
        precision = 4.89;
        satellitesAll = 15;
        satellitesSolution = 0;
        stantionLSNALL = 9;
        stantionLSNSolution = 5;
        iBeaconALL = 8;
        iBeaconSolution = 0;
        wifiRTTALL = 19;
        wifiRTTSolution = 0;
        break;
    }
    };


    valid = 1;
    devices = 7;
    modeGNSS = 1;


    char latitude_bytes[sizeof(float)];
    memcpy(latitude_bytes, &latitude, sizeof(float));
    char longitude_bytes[sizeof(float)];
    memcpy(longitude_bytes, &longitude, sizeof(float));
    char altitude_bytes[sizeof(float)];
    memcpy(altitude_bytes, &altitude, sizeof(float));
    char precision_bytes[sizeof(float)];
    memcpy(precision_bytes, &precision, sizeof(float));

    char body[33] = {36,0x04,0x03,0x00,0x1B};
    for(int i=0; i < 4; ++i)
    {
        body[i+5] = latitude_bytes[i];
        body[i+9] = longitude_bytes[i];
        body[i+13] = altitude_bytes[i];
        body[i+17] = precision_bytes[i];
    }
    body[21] = valid;
    body[22] = devices;
    body[22] = modeGNSS;
    body[24] = satellitesAll;
    body[25] = satellitesSolution;
    body[26] = stantionLSNALL;
    body[27] = stantionLSNSolution;
    body[28] = iBeaconALL;
    body[29] = iBeaconSolution;
    body[30] = wifiRTTALL;
    body[31] = wifiRTTSolution;

    char crc = crcCalc(body,32);
    body[32] = crc;
    printf("send Regular Navigation message\n");
    printCommandByBytes(body, sizeof(body));
    sendResponse(body,33);
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
        char body[6] = {36, 0x02, 0x03, 0x00,0x01,status};
        char crc = crcCalc(body, 5);
        char response[7] = {36, 0x02, 0x03, 0x00,0x01,status,crc};
        sendResponse(response,7);
        break;
    }


    case 1: //Запрос параметра
    {
        char param = getParamNavigationTelemerty();
        char body[7] = {36, 0x03, 0x03, 0x00,0x02, 0x00, param};
        char crc = crcCalc(body, 7);
        char response[8] = {36, 0x03, 0x03, 0x00,0x02, 0x00, param, crc};
        sendResponse(response,8);
        break;
    }
    }
}









//
//    float float_value = 43.5678;
//    char float_bytes[sizeof(float)];
//    memcpy(float_bytes, &float_value, sizeof(float));
