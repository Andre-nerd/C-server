#ifndef COMMON_UTILS_H_INCLUDED
#define COMMON_UTILS_H_INCLUDED

getStructCommand(char *head_buf, char *body_buf, STRUCT_COMMAND *output_data);
void printStructCommand(char *header, char *body);
void printCommandByBytes(unsigned char *body, int length_body);
unsigned char crcCalc(unsigned char *buf, int len);
get_bin_value(unsigned char v);

#endif // COMMON_UTILS_H_INCLUDED
