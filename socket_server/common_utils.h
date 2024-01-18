#ifndef COMMON_UTILS_H_INCLUDED
#define COMMON_UTILS_H_INCLUDED

STRUCT_COMMAND getStructCommand(char *head_buf, char *body_buf);
void printStructCommand(char *header, char *body);
void printCommandByBytes(unsigned char *body, int length_body);
unsigned char crcCalc(unsigned char *buf, int len);

#endif // COMMON_UTILS_H_INCLUDED
