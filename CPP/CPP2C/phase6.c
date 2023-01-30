#include <stdio.h>

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

int main()
{   
    B b = BCtor(1,2);
    printf("%d - %d\n", b.b.x, b.b.y);

    SetX(&b, 5);
    SetY(&b, 55);

     printf("%d - %d\n", b.b.x, b.b.y);


    return 0;
}