#include <iostream>


#define SHIFT (55)





void Check(int * p)
{
    char *needle = (char*)&p;
    if(*((needle + SHIFT)) == 77)
    {
        std::cout << "Yes" << '\n';
        return;
    }
    std::cout << "No" << '\n';
    std::cout << "Needle int: " << *(needle) << '\n';

}
int main()
{

    int a = 1986;
    int b = 1999;
    int c = 2000;

    int *p_a = &a;
    int *p_b = &b;
    int *p_c = &c;

   

    char *needle = (char*)&p_a;

    std::cout << &p_a << '\n';

    std::cout << &a << '\n';
    std::cout << p_a << '\n';

    std::cout << "Origin value: " << *p_a << '\n';

    // std::cout << "Addr : " << &p_a << '\n';
    // std::cout << "Addr size_t: " <<(size_t)p_a << '\n';
    // std::cout << "Needle int: " << *(char*)(needle + SHIFT) << '\n';

    *(needle + SHIFT) = 77;

    std::cout << "Origin value: " << *p_a << '\n';

    // std::cout << "Addr : " << &p_a << '\n';
    // std::cout << "Addr size_t: " <<(size_t)p_a << '\n';
    // std::cout << "Needle int: " << *(char*)(needle + SHIFT) << '\n';

    // std::cout << "Arr value: " << arr[0] << '\n';

    Check(p_a);
   



    return 0;
}