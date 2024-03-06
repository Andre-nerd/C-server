#include "const.h"
#include "common_utils.h"

char openFileForWrite(char* body, unsigned char length_data)
{
    //Открывает файл и устанавливает какие параметры в него писать
    components_for_recording = body[0];
    file_descriptor = 56;
    file_name_length1 = length_data-1;
    printf("file_name_lenght in openFun = %d\n",file_name_length1);
    for(int i = 1; i < length_data; ++i)//
    {
        file_name[i-1] = body[i];
    }
    printf("setting for record file:\n");
    printf("components_for_recording:");
    get_bin_value(components_for_recording);
    printf("file_descriptor = %d\n",file_descriptor);
    printf("file name:\n");
    for(int i = 0; i < length_data-1; i++)
    {
        printf("%c", file_name[i]);
    }
    printf("\n");
    return 0;
}

char getStatusOpenFileSolution(unsigned char * response)
{
    //Получаем дескриптор открытого файла, имя файла, компоненты записи
    printf("file_name_lenght in getStatusOpen = %d\n",file_name_length1);
    response[0] = components_for_recording;
    response[1] = file_descriptor;
    for(int i = 0; i < file_name_length1; ++i)//
    {
        printf("response add %d | %d\n",i, file_name[i]);

        response[i+2] = file_name[i];
    }
    return 0;
}
// Команда 0х05
void handlerOpenFileWriteCommand(STRUCT_COMMAND *input_data, void (*sendResponse)(char*, int))
{


    switch(input_data->header[1])// Смотрим спецификатор
    {
    case 0: //Команда на установку параметров
    {
        printf("handlerOpenFileWrite >> Command working >> lengthBody %d\n",input_data->header[3]);
        char status = openFileForWrite(input_data->body,input_data->header[3]);

        char body[7] = {36, 0x02, 0x05, 0x00, 0x02,status, file_descriptor};
        char crc = crcCalc(body, 7);
        char response[8] = {36, 0x02, 0x05, 0x00, 0x02,status, file_descriptor,crc};
        sendResponse(response,8);
        break;
    }


    case 1: //Запрос параметра
    {
        printf("handlerOpenFileWrite >> Request Param working\n ");
        unsigned char response[11] = {0};
        char status = getStatusOpenFileSolution(&response);
        unsigned char body[18] = {36, 0x03, 0x05,0x00, 0x0C, status};
        for(int i = 6; i < 17; i++)
        {
            body[i] = response[i-5];
        }

        char crc = crcCalc(body, 17);
        body[17] = crc;
        for(int i = 0; i < 17; i++)
        {
            printf("%d",body[i]);
        }

        sendResponse(body,18);
        break;
    }
    }
}


