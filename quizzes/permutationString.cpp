#include <iostream>
#include <stdio.h>


void Swap(char *x, char* y)
{
    char tmp = *x;
    *x = *y;
    *y = tmp;
}



void Perm(char *str, int left, int right)
{
    if(left == right)
    {
        std::cout << str << std::endl;
    }
    else
    {
        for(int i = left; i <= right; ++i)
        {
            Swap((str + left), (str + i));
            Perm(str, left + 1, right);
            Swap((str + left), (str + i));
        }
    }
}


int main()
{
    char arr[] = "ABC";
    Perm(arr, 0, 2);
    std::cout << arr << std::endl;

    return 0;
}