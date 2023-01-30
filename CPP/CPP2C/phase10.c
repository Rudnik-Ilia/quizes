#include <stdio.h>

typedef struct B B;

struct B
{
    int x;
};


static void Foo(B* b)
{
    printf("Static");
}



int main()
{
    struct B b = {1};


    Foo(&b);

  

    return 0;
}