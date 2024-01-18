#include "const.h"
#include "common_utils.h"

void sendRegularTelemetryMessage(void (*sendResponse)(char*, int))
{
    short batteryVoltage;
    short batteryCurrent;
    short weightRTK;
    short weightPPP;
    char batteryInfo;
    char setting;
    char lastAmendmentTimeRTK;
    char lastAmendmentTimePPP;

    batteryVoltage = 12;
    batteryCurrent = 1;
    weightRTK = 98;
    weightPPP = 77;
    batteryInfo = 28;
    setting = 0;
    lastAmendmentTimeRTK = 55;
    lastAmendmentTimePPP = 77;

    char batteryVoltage_bytes[sizeof(short)];
    memcpy(batteryVoltage_bytes, &batteryVoltage, sizeof(short));
    char batteryCurrent_bytes[sizeof(short)];
    memcpy(batteryCurrent_bytes, &batteryCurrent, sizeof(short));
    char weightRTK_bytes[sizeof(short)];
    memcpy(weightRTK_bytes, &weightRTK, sizeof(short));
    char weightPPP_bytes[sizeof(short)];
    memcpy(weightPPP_bytes, &weightPPP, sizeof(short));

    char body[17] = {36,0x04,0x04,0x0C};
    for(int i=0; i < 2; ++i)
    {
        body[i+4] = batteryVoltage_bytes[i];
        body[i+6] = batteryCurrent_bytes[i];
        body[i+8] = weightRTK_bytes[i];
        body[i+10] = weightPPP_bytes[i];
    }
    body[12] = batteryInfo;
    body[13] = setting;
    body[14] = lastAmendmentTimeRTK;
    body[15] = lastAmendmentTimePPP;


    char crc = crcCalc(body,16);
    body[16] = crc;
    printf("send Regular Telemetry message\n");
    printCommandByBytes(body, sizeof(body));
    sendResponse(body,17);
}
char setParamModuleTelemerty(char param)
{
    //������� ����������� ������� ���������� ��������� ���������� ������
    // 0 - �������� ���� ��� ��� ��������� ��������
    // 1 - 1��, 2 - 2 ��, 3 - 5 ��, 4 - 10 ��, 5 - 20 ��.
    // ���������� 0 ��� 0�10 - ������������ �������
    telemetry_frequency = param;
    return 0;
}

char getParamModuleTelemerty()
{
    //�������� ����������� ������� ���������� ��������� ���������� ������
    // 0 - �������� ���������
    // 1 - 1��, 2 - 2 ��, 3 - 5 ��, 4 - 10 ��, 5 - 20 ��.

    return 0x03;
}
// ������� 0�02
void handlerModuleTelemetryCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerModuleTelemetryCommand working\n ");

    switch(input_data->header[1])// ������� ������������
    {
    case 0: //������� �� ��������� ����������
    {

        char param = input_data->body[0];
        char status = setParamModuleTelemerty(param);
        char body[5] = {36, 0x02, 0x04, 0x01,status};
        char crc = crcCalc(body, 5);
        char response[6] = {36, 0x02, 0x04, 0x01,status,crc};
        sendResponse(response,6);
        break;
    }


    case 1: //������ ���������
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
