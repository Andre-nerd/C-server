#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;
enum {name_length = 50, b_length = 20};

struct coordinates {
    int x;
    int y;
    int z;
};

struct tag_fio{
    char name[name_length];
    char last[name_length];
};

struct tag_person{
    struct tag_fio fio;
    char sex;
    unsigned short old;
    char b_date[b_length];
};

int main()
{
    BYTE  byte = 12;
    printf("byte = %d\n", byte);

    struct coordinates cd;
    cd.x = 100;
    cd.y = 200;
    cd.z = 300;

    struct coordinates gh = {10,20,30};

    size_t sz = sizeof(cd);

    printf("x =%d, y = %d, z=%d, size = %d\n", cd.x,cd.y,cd.z, sz);
    printf("x =%d, y = %d, z=%d, size = %d\n", gh.x,gh.y,gh.z, sizeof(struct coordinates));

    struct tag_person person = {
        {
            "Andrey","Boukreev"
        },
        'm',
        52,
        "18.12.1971"
    };
    printf("name = %s, last name = %s\n", person.fio.name, person.fio.last );
    printf("sex = %c,b_date = %s\n", person.sex, person.b_date );

    strcpy(person.b_date,"18.12.1980");
    printf("sex = %c,b_date = %s\n", person.sex, person.b_date );


    struct tag_person p;
    p = person;
    strcpy(person.fio.name,"Sergey");
    strcpy(person.b_date,"18.12.1990");
    printf("name = %s, sex = %c, b_date = %s\n",p.fio.name, p.sex, p.b_date );
    printf("name = %s, sex = %c, b_date = %s\n",person.fio.name, person.sex, person.b_date );


    return 0;
}
