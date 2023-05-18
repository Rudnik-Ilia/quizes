#include <iostream>
#include <vector>
#include <thread>

#include "Transmitter.hpp"

using namespace ilrd;

void Thread1()
{
    auto chunk = std::make_shared<std::vector<char>>(5, 'O'); 
    Transmitter sender(chunk);
    sender.Send();
}

// void Thread2()
// {
//     auto chunk = std::make_shared<std::vector<char>>(5, 'A');
//     Transmitter sender(chunk);
//     sender.Send();
// }

// void Thread3()
// {
//     auto chunk = std::make_shared<std::vector<char>>(250, 'J');
//     Transmitter sender(chunk);
//     sender.Send();
// }

// void Thread4()
// {
//     auto chunk = std::make_shared<std::vector<char>>(25, 'D');
//     Transmitter sender(chunk);
//     sender.Send();
// }


int main()
{

    std::thread t1(Thread1);
    // std::thread t2(Thread2);
    // std::thread t3(Thread3);
    // std::thread t4(Thread4);

    sleep(1);

    t1.join();
    // t2.join();
    // t3.join();
    // t4.join();

    return 0;
}

