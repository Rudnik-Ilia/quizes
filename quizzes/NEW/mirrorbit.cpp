#include <iostream>
#include <bitset>


unsigned char Mir(unsigned char x)
{
    unsigned char res = 0;

    for(int i = 0; i < 8; ++i)
    {
        res <<= 1;
        res |= x & 1;
        x >>= 1;
    }

    return res;
}



int main()
{
    unsigned char a = 5;
    unsigned char b = Mir(5);


    std::cout << std::bitset<8>(a) << std::endl;
    std::cout << std::bitset<8>(b) << std::endl;
    
    return 0;
}