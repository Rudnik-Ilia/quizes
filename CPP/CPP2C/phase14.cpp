#include <iostream>

class A
{
    public:
   
    ~A(){};
};

class B: public A
{   
    public:
        int a;
        int b;
        int c;
        B(int x, int y, int z): a(x), b(y), c(z){}
};



int main()
{
    A* a = new B(2,3,4);

    delete a;
    return 0;
}