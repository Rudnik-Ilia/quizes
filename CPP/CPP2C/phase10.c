#include <stdio.h>


struct B
{
    int x;
};


static void Foo()
{
    printf("Static");
}



int main()
{
    struct B b = {1};

    
    Foo(&B);

  

    return 0;
}