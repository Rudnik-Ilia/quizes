#include <iostream>

#include "Receiver.hpp"

using namespace ilrd;

int main()
{
    Receiver minion(8080);
    minion.Listen();

    std::cout << "STOP SERVER" << std::endl;

    return 0;
}