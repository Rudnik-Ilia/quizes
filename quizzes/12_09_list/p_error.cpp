#include <iostream>

void PrintReverse(int num)
{
    int enable_print = num % 10;

    while (num)
    {
        if(0 == enable_print && num % 10 != 0)
        {
            enable_print = 1;
        }
        if(1 == enable_print)
        {
            printf("%d", num % 10);
            num /= 10;
        }
    }
}

void PrintReverse2(int num)
{
    while (num)
    {
        printf("%d", num % 10);
        num /= 10;
    }
}

int main()
{
    PrintReverse2(1234);
    return 0;
}