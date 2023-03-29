
#define CREATOR
#include <iostream>
#include "Handleton.hpp"
#include "Scheduler.hpp"

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
    ilrd::Logger* GetInstanceLogger()
    {
        return ilrd::Handleton<ilrd::Logger>::GetInstance();
    }

    ilrd::Scheduler* GetInstanceScheduler()
    {
        return ilrd::Handleton<ilrd::Scheduler>::GetInstance();
    }

}