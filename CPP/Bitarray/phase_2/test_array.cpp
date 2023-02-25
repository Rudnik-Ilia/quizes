#include <iostream>
using std::cout;
using std::endl;
#include  <limits.h>
#include "bitarray.hpp"
using namespace ilrd;





int main()
{
    const size_t s = 127;
    std::string str;

    BitArray<s> b1;

    b1.set(6, true);
    b1.set(1, true);
    b1.set(0, true);
    b1.set(63, true);
    b1.set(true);

    b1.set(63, false);
    b1.set(true);
    b1.set(0, false);
    b1.flip(5);
    b1.flip(5);
    b1.flip(0);
    b1[0] = false;
 
  
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
    




    
    

    return 0;
}