#include <iostream>
using std::cout;
using std::endl;
#include  <limits.h>
#include "bitarray.hpp"
using namespace ilrd;



void Foo(const BitArray& x)
{
    if(!x[1])
    {
        cout << "!!!" << endl;
    }
}
void Faa(BitArray x)
{
    if(!x[1])
    {
        cout << "???" << endl;
    }
}


int main()
{
    BitArray b1;
    BitArray b2;

    // const BitArray& ref = b1;

    // Foo(ref);
    // Faa(b1);

    b1[1] = true;

    // b1[1] = b2[2];
    cout << (size_t)true << endl;
   

    
    

    return 0;
}