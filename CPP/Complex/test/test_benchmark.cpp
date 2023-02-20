#include <iostream>
#include "complex.hpp"

using namespace ilrd;





int main()
{
    size_t count = 10000000;
    ComplexNum x(1.1, 2.2);
    ComplexNum y(1.1, 2.2);
        
    ComplexNum& x1 = x;
    ComplexNum& y1 = y;

    
    while(count)
    {
        ComplexNum res = x1 + y1;
        count--;
    }

}