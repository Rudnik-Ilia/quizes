#include <iostream>
#include "complex.hpp"
#include "test.h"

using namespace ilrd;


int main()
{
    ComplexNum x1(9.9, 3.14);
    ComplexNum x11(9.9, -3.14);
    ComplexNum x3(10.15, 30.20);
    ComplexNum x4 = x1 + x3;
    x1+=x3;


    std::cout << x1.GetReal() << " " << x1.GetImag() << std::endl;
    std::cout << x4.GetReal() << " " << x4.GetImag() << std::endl;
    std::cout << (x1 == x4) << std::endl;
    
   
    std::cout << "---------------------------------------"<< std::endl;


    ComplexNum x2 = ComplexNum(x1);

    std::cout << x2.GetReal() << std::endl;
    std::cout << x2.GetImag() << std::endl;


    std::cout << x11 << std::endl;




    return 0;
}