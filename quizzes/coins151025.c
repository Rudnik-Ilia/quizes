#include <stdio.h>


int Change(int summ)
{
    int res = 0;
    
    if(summ == 0)
    {
        return 1;
    }   
    if(summ >= 0)
    {
        res += Change(summ - 50);
    }
    if(summ >= 0)
    {
        res += Change(summ - 25);
    }
    if(summ >= 0) 
    {
        res += Change(summ - 10);
    }
    if(summ >= 0)
    {
        res += Change(summ - 5);
    }
    if(summ >= 0)
    {
        res += Change(summ - 1);
    }
    return res;
}






int main()
{
    printf("%d\n", Change(5));




    return 0;
}


