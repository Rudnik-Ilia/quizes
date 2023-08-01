#include <iostream>


int Can(int total)
{
    int res = 0;

    if(total == 0)
    {
        return 1;
    }
    if(total >= 0)
    {
        res += Can(total - 3);
    }
    if(total >= 0)
    {
        res += Can(total - 1);
    }

    return res;
}

void Can2(int total, int big, int small)
{
    int res = total % (3*big);
    std::cout << res << std::endl;
    int res2 = res % (small*2);
    std::cout << res2 << std::endl;

}
int Foo(int *val)
{
    return * val = *val + 5;
}

int main()
{
    // std::cout << Can2(5, 3, 1) << std::endl;
    std::cout << (5 % (-8)) << std::endl;
    std::cout << (-12)/5 << std::endl;
    std::cout << (-12)%5 << std::endl;
    std::cout << (5)/-8 << std::endl;
    // Can2(5, 2, 1);

    int x = 5;
    Foo(&x);

    std::cout << x << std::endl;

    return 0;
}