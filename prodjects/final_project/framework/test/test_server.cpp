#include <iostream>

#include "Receiver.hpp"

using namespace ilrd;

int main()
{
    Receiver minion;
    minion.Listen();

    std::cout << "STOP SERVER" << std::endl;

    return 0;
}