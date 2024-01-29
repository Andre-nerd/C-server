#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#define HEADER_SIZE 5
#define TIME_WAIT_SOCKET 200000
#define SHORT_RESPONSE_LENGTH 6
#define F_NAME_LENGTH 9
typedef struct
{
    char header[HEADER_SIZE];
    char body[50];
} STRUCT_COMMAND;

typedef struct
{
    unsigned char short_response[SHORT_RESPONSE_LENGTH];
    unsigned char long_response[30];
} STRUCT_RESPONSE;

enum commands {
    on_off_command = 0x00, devices_for_solution = 0x01, amendment_manage =  0x02, navigation_telemetry = 0x03,
    module_telemetry = 0x04, open_file_write = 0x05, close_file_write = 0x06, request_common_param = 0x07,
    subsribe_amendment = 0x08
};
enum specifications {
    direction = 0x00,
    request_param = 0x01,
    response_direction = 0x02,
    response_param = 0x03,
    regular_message = 0x04

};

int imitation_cycle_navigation;
int imitation_cycle_telemetry;

// ¬ременное хранилище параметров устройства
char telemetry_frequency; // „астота выдачи регул€рного сообщени€ с данными телеметрии модул€
char navigation_frequency; // „астота выдачи регул€рного сообщени€ с данными навигации

// ¬ременное хранилище параметров записи в файл
char components_for_recording;
char file_descriptor;
char file_name[F_NAME_LENGTH];

//ѕитание модема  GSM, подписки на поправки
char settingAmendment;


#endif // CONST_H_INCLUDED
