#include <iostream>
#include <vector>
#include <thread>

#include "Transmitter.hpp"

using namespace ilrd;

void Thread1()
{
    auto chunk = std::make_shared<std::vector<char>>(50, 'O'); 
    Transmitter sender;
    sender.Send(chunk, 55);
}

void Thread2()
{
    std::string word = "ABC"; 
    int arr[] = {3,50,700}; 
    for(int i = 0; i < word.size();  ++i)
    {
        auto chunk = std::make_shared<std::vector<char>>(arr[i], word[i]);
        Transmitter sender;
        sender.Send(chunk, 77);
    }
}

void Thread3()
{
    std::string word = "RUDNIK"; 
    int arr[] = {100000,150000,200000,133000,50000, 5000}; 
    for(int i = 0; i < word.size();  ++i)
    {
        auto chunk = std::make_shared<std::vector<char>>(arr[i], word[i]);
        Transmitter sender;
        sender.Send(chunk, 0);
    }
}

void Thread4()
{
    std::string word = "QWERTY"; 
    int arr[] = {3,5,7,8,9}; 
    for(int i = 0; i < word.size();  ++i)
    {
        auto chunk = std::make_shared<std::vector<char>>(arr[i], word[i]);
        Transmitter sender;
        sender.Send(chunk, 111);
    }
}   


int main()
{

    // std::thread t1(Thread1);
    // std::thread t2(Thread2);
    std::thread t3(Thread3);
    // std::thread t4(Thread4);

    sleep(1);

    // t1.join();
    // t2.join();
    t3.join();
    // t4.join();

    return 0;
}

