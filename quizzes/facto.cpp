#include <iostream>
#include "Timer.hpp"


size_t Fac(size_t x)
{
    if(x == 0)
    {
        return 1;
    }
    else
    {
        return x * Fac(x - 1);
    }
}

size_t Fac1(size_t x)
{
    if(x > 0)
    {
        return x * Fac(x - 1);
    }
    else
    {
        return 1;
    }
}

size_t Fac2(size_t x)
{
    if(x > 0)
    {
        return x * Fac2(x - 1);
    }
    else
    {
        return 1;
    }
}

size_t Fac3(size_t x)
{
    if(x == 0 || x == 1)
    {
        return 1;
    }
    if( x == 2)
    {
        return 2;
    }
    else
    {
        return x * Fac3(x - 1);
    }
}

size_t Fac4(size_t x, size_t a)
{
    if(x == 0)
    {
        return a;
    }
    else
    {
        return Fac4(x - 1, a * x);
    }
}


int Fac5(int x, int a)
{
    if(x > 0)
    {
        return Fac5(x - 1, a * x);
    }
    else
    {
        return a;
    }
}
struct A
{
    public:
    int x;
    protected:
    int y;
    private:
    int z;
};

struct B : public A
{
 
};




int main()
{   
    MyTimer t;
   

    // std::cout << Fac(12) << std::endl;
    // std::cout << Fac1(12) << std::endl;
    // std::cout << Fac2(12) << std::endl;
    // std::cout << Fac3(12) << std::endl;
    // std::cout << Fac4(12, 1) << std::endl;
    // std::cout << Fac5(12, 1) << std::endl;

    A* a = new B();
   
    

   


    return 0;
}