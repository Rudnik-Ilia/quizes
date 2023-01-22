#include <iostream>
#include "complex.hpp"
#include "test.h"

using namespace ilrd;


int main()
{
    ComplexNum x0(0.0, 0.0);
    ComplexNum x1(9.9, 3.14);
    ComplexNum x1d(9.9, 3.14);
    ComplexNum x2d(9.9, 3.14);
    ComplexNum x11(9.9, -3.14);
    ComplexNum x3(10.15, 30.20);
    ComplexNum x4 = x1 + x3;
    x1+=x3;
    
    TEST("test1",  x11.GetReal() , 9.9);
    TEST("test1",  x11.GetImag() , -3.14);

    TEST("test1",  x3.GetReal() , 10.15);
    TEST("test1",  x3.GetImag() , 30.20);

    std::cout << x1.GetReal() << " " << x1.GetImag() << std::endl;
    std::cout << x4.GetReal() << " " << x4.GetImag() << std::endl;

    TEST("test1",  (x1 == x4) , 1);
    TEST("test1",  (x1 != x11) , 1);
    
   
    std::cout << "---------------------------------------"<< std::endl;


    ComplexNum x2 = ComplexNum(x1);

    TEST("test1",  (x1 == x2) , 1);


    std::cout << x1 << std::endl;
    std::cout << x2 << std::endl;
    std::cout << x3 << std::endl;
    std::cout << x4 << std::endl;
    std::cout << x11 << std::endl;

    ComplexNum x6 = x3;


    try
    {
        // x1/=x0; by zero
        x3/=x11;
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    ComplexNum x7 = x6/x11;

    TEST("test1",  (x3 == x7) , 1);



    std::cout << x1d << " * " << x11 << " = " << (x1d*=x11) << std::endl;
    std::cout << x2d << " * " << x11 << " = " << std::endl;
    ComplexNum x5 = x2d*x11;
    std::cout << x5 << std::endl;

    TEST("test1",  (x1d == x5) , 1);








    return 0;
}