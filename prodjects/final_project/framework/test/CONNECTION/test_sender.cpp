#include <iostream>
#include <vector>


#include "Transmitter.hpp"

using namespace ilrd;


int main()
{
    auto chunk = std::make_shared<std::vector<char>>(130003, 'j'); 
    Transmitter sender(chunk);
    sender.Send();

    return 0;
}
