#include <iostream>
#include "Timer.hpp"

using namespace std;

size_t FibRec(size_t x)
{
    if(x == 0)
    {
        return 0;
    }
    if((x == 1) || (x == 2))
    {
        return 1;
    }
    return FibRec(x - 1) + FibRec(x - 2);
}

size_t FibLoop(size_t x)
{
    size_t prev = 0;
    size_t cur = 1;
    size_t next = prev + cur;

    for(size_t i = 2; i < x; ++i)
    {
        prev = cur;
        cur = next;
        next = prev + next;
    }
    return next;
}

int fib(int n, int a = 0, int b = 1) 
{
    if (n == 0) 
    {
        return a;
    }
    if (n == 1 || n == 2) 
    {
        return b;
    }
    return fib(n - 1, b, a + b);
}


int main()
{
    // MyTimer t;
    cout << FibRec(45) << endl;
    // cout << FibLoop(80) << endl;
    // cout << fib(11, 1, 1) << endl;
    // cout << FibRec(11) << endl;




    return 0;
}


