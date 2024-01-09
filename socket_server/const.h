#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#define HEADER_SIZE 4
struct command_package
{
    char header[HEADER_SIZE];
    unsigned char length_body;
    char body[30];
};

#endif // CONST_H_INCLUDED
