#pragma once

#include <iostream>

class SimpleTest
{
    public:
       SimpleTest(){}
       void My_method()
       {
            std::cout << "Just class - " << this << std::endl; 
       }

};