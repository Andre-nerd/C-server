#include "const.h"
#include "common_utils.h"


// ������� 0�07
void handlerRequestParamModuleCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerRequestParamModuleCommand working\n ");

    //��������� �������� �����. �� ��������� ���������� ������ ����� �� ������ ���������, ������������ 0�03
    int id = 770409012;
    char id_bytes[sizeof(int)];
    memcpy(id_bytes, &id, sizeof(int));
    unsigned char status = 0;
    unsigned char response[16] = {36,0x03,0x07,0x00,0x0A,status,components_for_recording,
     settingAmendment, navigation_frequency,telemetry_frequency,
     id_bytes[0], id_bytes[1], id_bytes[2], id_bytes[3], systemCoordinates
     };
    unsigned char crc = crcCalc(response, 15);
    response[15] = crc;
    sendResponse(response,16);

}
