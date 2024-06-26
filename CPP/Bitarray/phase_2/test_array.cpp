#include <iostream>
using std::cout;
using std::endl;
#include  <limits.h>
#include "bitarray.hpp"
using namespace ilrd;


int main()
{
    const size_t s = 124;
    std::string str;

    BitArray<s> b1, b2;
    BitArray<130> b3;

    b1.set(6, true);
    b1.set(1, true);
    b1.set(0, true);
    b1.set(63, true);
    b1.set(true);

    b1.set(63, false);
    b1.set(true);
    b1.set(0, false);
    b1.flip(5);
    b1.flip(0);
    b1[0] = false;
   

    b1.set(true);
    

    b1.set(0, false);
    b1.set(2, false);
   
    b2.set(1, false);

    cout << (b1 == b2) << endl;

    b1 |= b2;

    b1 &= b2;
    b1 ^= b2;
    b1.set(8, true);
    b1.set(119, true);
    b1.set(122, true);
    b1.set(1, true);
    b1.set(6, true);
    b1.set(68, true);
    b1.set(8, true);
    b2.set(5, true);
    b1[5] = b2[5];

    // // b1[126] = true;
    

 
  
    for(int i = 0; i < 128 ; ++i)
    {
        if((i % 64) == 0)
        {
           cout << '\n'; 
           cout << '\n'; 
        }
        if(i  == s)
        {
          
           cout << '|'; 
        }
        cout << b1.get(i) << ' ';
    }

    for(int i = 0; i < 128 ; ++i)
    {
        if((i % 64) == 0)
        {
           cout << '\n'; 
           cout << '\n'; 
        }
        if(i  == s)
        {
          
           cout << '|'; 
        }
        cout << b2.get(i) << ' ';
    }

    cout <<'\n'<< b1.count() << endl;
    b1.set(0, true);
    
    cout << b1.to_string() << endl;

    
    

    return 0;
}