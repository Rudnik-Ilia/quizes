#include <stdio.h>
#include <stdlib.h>

typedef struct B B;

struct private
{
    int x;
    int y;
};

struct B
{
    struct private b;

};

struct B BCtor(int data1, int data2)
{
    struct B this = {.b.x = data1, .b.y = data2};
    return this;
}

void SetX(B* st, int data)
{
    st->b.x = data;
};

void SetY(B* st, int data)
{
    st->b.y = data;
};

void BDtor(B* b)
{   
    free(b);
    printf("Im desrurctor B\n");
}



int main()
{   
    B b = BCtor(1,2);
    printf("%d - %d\n", b.b.x, b.b.y);

    SetX(&b, 5);
    SetY(&b, 55);

    printf("%d - %d\n", b.b.x, b.b.y);

    B* p_b = malloc(sizeof(struct B));

    *p_b = BCtor(0,0);

    printf("%d - %d\n", p_b->b.x, p_b->b.y);

    SetX(p_b, 3);
    SetY(p_b, 33);

    printf("%d - %d\n", p_b->b.x, p_b->b.y);

    /*
    
    BDtor(p_b);
    */

    B array1[100];
	B *array2 = malloc(sizeof(struct B) * 100);


    return 0;
}