#include "const.h"
#include "common_utils.h"

char openFileForWrite(char* body)
{
    //Открывает файл и устанавливает какие параметры в него писать
    components_for_recording = body[0];
    file_descriptor = 56;
    for(int i = 1; i < F_NAME_LENGTH+1; ++i)//
    {
        file_name[i-1] = body[i];
    }
    printf("setting for record file:\n");
    printf("components_for_recording:");
    get_bin_value(components_for_recording);
    printf("file_descriptor = %d\n",file_descriptor);
    for(int i = 0; i < F_NAME_LENGTH; i++){
        printf("%c", file_name[i]);
    }
    return 0;
}

char getStatusOpenFileSolution(unsigned char * response)
{
    //Получаем дескриптор открытого файла, имя файла, компоненты записи
    response[0] = components_for_recording;
    response[1] = file_descriptor;
    for(int i = 0; i < F_NAME_LENGTH; ++i)//
    {
        response[i+2] = file_name[i];
    }
    return 0;
}
// Команда 0х05
void handlerOpenFileWriteCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{
    printf("handlerOpenFileWriteCommand working\n ");

    switch(input_data->header[1])// Смотрим спецификатор
    {
    case 0: //Команда на установку параметров
    {
        char status = openFileForWrite(input_data->body);

        char body[7] = {36, 0x02, 0x05, 0x00, 0x02,status, file_descriptor};
        char crc = crcCalc(body, 7);
        char response[8] = {36, 0x02, 0x05, 0x00, 0x02,status, file_descriptor,crc};
        sendResponse(response,8);
        break;
    }


    case 1: //Запрос параметра
    {
        unsigned char response[11] = {0};
        char status = getStatusOpenFileSolution(response);
        unsigned char body[18] = {36, 0x03, 0x05,0x00, 0x0C, status};
        for(int i = 5; i < 17; i++){
            body[i] = response[i-5];
        }

        char crc = crcCalc(body, 17);
        body[17] = crc;
        sendResponse(body,18);
        break;
    }
    }
}


