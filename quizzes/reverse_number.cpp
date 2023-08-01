#include <iostream>


int Rev(int x)
{
    int tmp = 0;
    int res = 0;

    while(x)
    {
        tmp = x % 10;
        res = tmp + res*10;
        x /= 10;
    }
    return res;
}
int Rec(int x, int res)
{
    if(x == 0)
    {
        return res;
    }
    res = x % 10 + res*10;
    return Rec(x/10, res);
}



int Rev2(int num)
{
    int res = 0;

    while(num)
    {
        res = res*10 + num % 10;
        num = num / 10;
    }
    return res;
}

int Rec2(int num, int res)
{
    if(num == 0)
    {
        return res;
    }
    int tmp = num % 10;
    res = res*10 + tmp;

    return Rec2(num/10, res);
}




int main()
{
    std::cout << Rec2(123, 0) << std::endl;
    return 0;
}