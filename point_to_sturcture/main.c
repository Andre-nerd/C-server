#include <stdio.h>
#include <stdlib.h>

struct tag_vector{
    double x;
    double y;
};
int main()
{

    struct tag_vector v = {1.2, 4.7};
    struct tag_vector* ptr_v;
    ptr_v = &v;

    (*ptr_v).x = 12;
    double y  = (*ptr_v).y;

    // Другой способ обращения к полям структуры
    ptr_v->x = 14;
    double y1 = ptr_v -> y;

    // В куче

    struct tag_vector* ptr_D = malloc(sizeof(struct tag_vector));
    ptr_D -> x = 34.1;
    printf("%.2f", ptr_D->x);

    free(ptr_D);
    return 0;
}
