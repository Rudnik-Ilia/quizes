#include <stdio.h>
#include <stdlib.h>
typedef struct A A;
typedef struct B B;
typedef struct C C;

struct A
{
    int x;
    int y;
};

/*
struct B
{
    struct A a;
    int z;
};

A ACtor(int a, int b)
{
    A this = {.x = a, .y = b};
    return this;
}

B BCtor(int c)
{
    B this = {.a = ACtor(0,0), .z = c};
    return this;
}
*/
struct C
{
    void* parent;
    int x;
};

struct B
{
    void* parent;
    int z;
};

A* ACtor(int a, int b)
{
    A* this = malloc(sizeof(A));
    this->x = a;
    this->y = a;
    return this;
}

C* CCtor(int a)
{
    C* this = malloc(sizeof(C));
    this->x = a;
    return this;
}


B* BCtor(int z, int child)
{
    B* this = malloc(sizeof(B));
    if(child == 1)
    {
        this->parent = ACtor(1,2);
    }
    if(child == 2)
    {
        this->parent = CCtor(1);
    }

    this->z = z;
    return this;
}




int main()
{
    B *b = BCtor(5, 1);
/*
    printf("%d - %d - %d\n", b->a.x, b.a.y, b.z);
*/

    printf("%d - %d - %d\n", ((A*)(b->parent))->x, ((A*)(b->parent))->y, b->z);

    return 0;
}