
#include <iostream>
#include "Reactor.hpp"
#include "Listener.hpp"

using namespace ilrd;

// gp11 test_reactor.cpp ../src/Reactor.cpp -I ../include

void Foo()
{
    std::cout << "FOO" << std::endl;
}



int main()
{


    std::unique_ptr<Listener> p_lis(new Listener());

    Reactor reactor(std::move(p_lis));

    reactor.Register();

    
    
    




    return 0;
}