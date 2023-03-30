#include <iostream>
#include <unistd.h>

#include "Asyncinjection.hpp"

using namespace ilrd;

bool foo_true()
{
    std::cout <<"foo_true prints" << std::endl;
    return true;
}
int i = 0;

bool foo_false()
{
    if(i != 5)
    {
        std::cout <<"foo_false prints" << std::endl;
        ++i;
        return false;
    }
    std::cout <<"foo_false is finally true" << std::endl;
    return true;
}

int main()
{
    
    AsyncInjection *ai_true = new AsyncInjection(foo_true, std::chrono::milliseconds(1000));
    AsyncInjection *ai_false = new AsyncInjection(foo_false, std::chrono::milliseconds(1500));



    sleep(10);


    return 0;
}
