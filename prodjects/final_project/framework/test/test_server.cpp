#include <iostream>

#include "Receiver.hpp"

using namespace ilrd;

int main()
{
    Receiver r;
    r.Listen();

    std::cout << "STOP SERVER" << std::endl;

    return 0;
}