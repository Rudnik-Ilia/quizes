#include <stdio.h>

size_t Fib(size_t x)
{
    if(x == 0)
    {
        return 0;
    }
    if((x == 1) || (x == 2))
    {
        return 1;
    }

    return Fib(x - 1) + Fib(x - 2);
}

int main()
{
    printf("%ld\n", Fib(45));
    return 0;
}