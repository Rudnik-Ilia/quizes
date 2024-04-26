#include <stdio.h>


int Find(char *str)
{
    int count = 0;
    int flag = 0;

    while (*str)
    {
        if(*str >= '0' && *str <= '9')
        {
            if(flag == 1)
            {
                ++str;
                continue;
            } 
            flag = 1;
            ++count;
            ++str;
        }
        else
        {
            flag = 0;
            ++str;
        }
    }
    return count;
}

int main()
{
    char *str = "qwer4768798798756464qwe3qw4e4";

    printf("%d\n", Find(str));
    return 0;
}