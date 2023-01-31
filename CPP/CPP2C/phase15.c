#include <stdio.h>

typedef struct A A;
typedef struct B B;

struct A_func_ptr
{
    void (*show)(A* this);
};
struct B_func_ptr
{
    void (*show)(B* this);
};

struct A
{
    struct A_func_ptr* _vptr;
    int x;
};

struct B
{
    struct A_func_ptr* _vptr;
    int x;
};

void show(A *this)
{
    printf("A Struct X: %d\n", this->x);
}

void Bshow(B *this)
{
     printf("B Struct X: %d\n", ((A*)this)->x);
}

struct A_func_ptr a_vable = 
{ 
    show
};
struct B_func_ptr b_vable = 
{ 
    Bshow
};

void ACtor(A* a)
{
    a->_vptr = &a_vable;
    a->x = 99;
}

void BCtor(B* b)
{
    b->_vptr = (A*)&b_vable;
    b->x = 11;
}

void Foo(A* a)
{
    a->_vptr->show(a);
}


int main()
{

    A a;
    B b;

    ACtor(&a);
    BCtor(&b);

    Foo(&b);





    return 0;
}