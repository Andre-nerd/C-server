#include <stdio.h>
#include <stdlib.h>
struct command_package {
    short body[4];
    int length_body;
};

struct command_package getCommand(){
    struct command_package package = {
    {3,5,7,89},
    4
    };

    return package;
}

int main()
{
    struct command_package command = getCommand();
    printf("Packed");
    printf("length %d\n", command.length_body);
    for(int i = 0; i < command.length_body; ++i){
        printf("%d",command.body[i]);
    }
    printf("\n");

    char q;
    scanf("%d",&q);

    return 0;
}
