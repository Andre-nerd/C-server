#include "const.h"
#include "common_utils.h"


// ������� 0�07
void handlerRequestParamModuleCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerRequestParamModuleCommand working\n ");

    //��������� �������� �����. �� ��������� ���������� ������ ����� �� ������ ���������, ������������ 0�03
    unsigned char status = 0;
    unsigned char response[11] = {36,0x03,0x07,0x06,status,components_for_recording, settingAmendment, navigation_frequency,telemetry_frequency };
    unsigned char crc = crcCalc(response, 10);
    response[10] = crc;
    sendResponse(response,11);

}
