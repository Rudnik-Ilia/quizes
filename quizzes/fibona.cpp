#include <iostream>
#include "Timer.hpp"

using namespace std;

int FibRec(int x)
{
    if(x == 0)
    {
        return 0;
    }
    if((x == 1) | (x == 2))
    {
        return 1;
    }
    return FibRec(x - 1) + FibRec(x - 2);
}

int FibLoop(int x)
{
    int prev = 0;
    int cur = 1;
    int next = prev + cur;

    for(int i = 2; i < x; ++i)
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
    // cout << FibRec(300) << endl;
    cout << FibLoop(6) << endl;
    // cout << fib(300) << endl;

    return 0;
}


