#include <iostream>
#include <vector>
#include <thread>

#include "Transmitter.hpp"

using namespace ilrd;

Transmitter sender(8080);

// void Thread1(size_t times)
// {
//     auto chunk = std::make_shared<std::vector<char>>(times, 'X'); 
//     Transmitter sender;
//     sender.Send(chunk, 0, 1);
// }

void Thread2()
{
    auto chunk = std::make_shared<std::vector<char>>(100001, 'X'); 
    sender.Send(chunk, 0, 1);
}

void Thread3()
{
    std::string word = "RUDNIK"; 
    int arr[] = {131072,151000,222000,131072,57000, 9000}; 
    for(int i = 0; i < word.size();  ++i)
    {
        auto chunk = std::make_shared<std::vector<char>>(arr[i], word[i]);
        // Transmitter sender;
        sender.Send(chunk, 0, 1);
    }
}

void Thread4()
{
    std::string word = "QW"; 
    int arr[] = {33000,170000}; 
    for(int i = 0; i < word.size();  ++i)
    {
        auto chunk = std::make_shared<std::vector<char>>(arr[i], word[i]);
        // Transmitter sender;
        sender.Send(chunk, 111, 1);
    }
}   
// void Thread5()
// {
//     std::string word = "QAS"; 
//     int arr[] = {100000, 77000, 30000}; 
//     for(int i = 0; i < word.size();  ++i)
//     {
//         auto chunk = std::vector<char>(arr[i], word[i]);
//         Transmitter sender;
//         sender.Send(chunk, 111, 1);
//     }
// }   
// void Thread6()
// {
//     std::string word = "Q"; 
//     int arr[] = {100000}; 
//     for(int i = 0; i < word.size();  ++i)
//     {
//         auto chunk = std::vector<char>(arr[i], word[i]);
//         Transmitter sender;
//         sender.Send(chunk, 111, 1);
//     }
// }   


int main(int argc, char *argv[])
{
    // auto chunk = std::make_shared<std::vector<char>>(9000, 'X'); 
    // sender.Send(chunk, 0, 1);

    // size_t param = atoi(argv[1]);
    // std::thread t1(Thread1, param);
    std::thread t2(Thread2);
    std::thread t3(Thread3);
    std::thread t4(Thread4);
    // std::thread t5(Thread5);
    // std::thread t6(Thread6);

    sleep(1);

    // t1.join();
    t2.join();
    t3.join();
    t4.join();
    // t5.join();
    // t6.join();

    return 0;
}

