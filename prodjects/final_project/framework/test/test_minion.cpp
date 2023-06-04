#include <iostream>

#include "Minion.hpp"
#include "Transmitter.hpp"

using namespace ilrd;

int main()
{
    Minion minion(8080);

    minion.Wait();

    std::cout << "STOP SERVER" << std::endl;

    return 0;
}