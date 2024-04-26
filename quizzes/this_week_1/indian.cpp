#include <iostream>

// char IsLittle(int x)
// {
//     return ((char*)&x + 2); 
// }

int main()
{
    unsigned int x = 0x1234;
    unsigned int* p_x = &x;
    char * ptr = ((char*)&p_x);
    std::cout << ptr << std::endl;
    return 0;
}