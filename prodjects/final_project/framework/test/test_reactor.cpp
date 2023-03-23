
#include <iostream>
#include <unistd.h>

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
    int x;
    std::unique_ptr<Listener> p_lis(new Listener());

    Reactor reactor(std::move(p_lis));

    Reactor::EventCallback callback(Foo);

    reactor.Register(Reactor::EventKey(0, Reactor::ioMode::READ), callback);
    reactor.Register(Reactor::EventKey(1, Reactor::ioMode::WRITE), callback);
    reactor.Run();

    std::cout << 3;
    std::cin >> x;

    sleep(5);



    
    
    return 0;
}