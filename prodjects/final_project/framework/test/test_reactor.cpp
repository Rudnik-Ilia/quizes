
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "Reactor.hpp"
#include "Listener.hpp"

using namespace ilrd;

// gp11 test_reactor.cpp ../src/Reactor.cpp -I ../include

std::unique_ptr<Listener> p_lis(new Listener());
Reactor reactor(std::move(p_lis));

void Foo()
{
    std::cout << "FOO" << std::endl;
    reactor.Unregister(Reactor::EventKey(STDIN_FILENO, Reactor::ioMode::READ));
}

void StopFunc()
{
    char buffer[2] = {0};
    read(STDIN_FILENO, &buffer, 1);
    if(0 == strcmp(buffer, "x"))
    {
        reactor.Stop();
    }
}



int main()
{
    Reactor::EventCallback callback(Foo);
    Reactor::EventCallback callbackStop(StopFunc);

    // reactor.Register(Reactor::EventKey(1, Reactor::ioMode::WRITE), callback);
    // reactor.Register(Reactor::EventKey(STDIN_FILENO, Reactor::ioMode::READ), callback);
    reactor.Register({STDIN_FILENO, Reactor::ioMode::READ}, callbackStop);

    reactor.Run();




    
    
    return 0;
}