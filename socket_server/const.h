#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#define HEADER_SIZE 4
#define SHORT_RESPONSE_LENGTH 6
typedef struct
{
    char header[HEADER_SIZE];
    char body[30];
} STRUCT_COMMAND;

typedef struct
{
    unsigned char short_response[SHORT_RESPONSE_LENGTH];
    unsigned char long_response[30];
} STRUCT_RESPONSE;

enum commands {
    on_off_command = 0x00, devices_for_solution = 0x01
};
enum specifications {
    direction = 0x00,
    request_param = 0x01,
    response_direction = 0x02,
    response_param = 0x03,
    regular_message = 0x04

};

#endif // CONST_H_INCLUDED
