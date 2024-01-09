#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#define HEADER_SIZE 4
struct command_package
{
    char header[HEADER_SIZE];
    char body[30];
};

enum commands {
    on_off = 0x00
};
enum specifications {
    direction = 0x00,
    request_param = 0x01,
    response_direction = 0x02,
    response_param = 0x03,
    regular_message = 0x04

};

#endif // CONST_H_INCLUDED
