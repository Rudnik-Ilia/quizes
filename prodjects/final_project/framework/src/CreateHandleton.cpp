
#define CREATOR
#include <iostream>
#include "Handleton.hpp"

#include "Logger.hpp"



void __attribute__((constructor)) Greeting() 
{
    std::cout << "Hello" << std::endl;
}

void __attribute__((destructor)) Bye() 
{
    std::cout << "Bye" << std::endl;
}

extern "C"
{
    ilrd::Logger* GetInstance()
    {
        return ilrd::Handleton<ilrd::Logger>::GetInstance();
    }

}