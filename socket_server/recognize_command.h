#ifndef RECOGNIZE_COMMAND_H_INCLUDED
#define RECOGNIZE_COMMAND_H_INCLUDED


struct command_package;
struct command_package recognize(struct command_package *input_data);
void recognizeType(char *header[], unsigned char body_size, char *body[]);


#endif // RECOGNIZE_COMMAND_H_INCLUDED
