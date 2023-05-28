#include <iostream>
#include <vector>
#include <thread>

#include "Transmitter.hpp"

using namespace ilrd;

void Thread1(size_t times)
{
    auto chunk = std::make_shared<std::vector<char>>(times, 'X'); 
    Transmitter sender;
    sender.Send(chunk, 0, 1);
}

void Thread2()
{
    std::string word = "ABC"; 
    int arr[] = {3,50,700}; 
    for(int i = 0; i < word.size();  ++i)
    {
        auto chunk = std::make_shared<std::vector<char>>(arr[i], word[i]);
        Transmitter sender;
        sender.Send(chunk, 77, 1);
    }
}

void Thread3()
{
    std::string word = "RUDNIK"; 
    int arr[] = {123000,151000,222000,133000,57000, 9000}; 
    for(int i = 0; i < word.size();  ++i)
    {
        auto chunk = std::make_shared<std::vector<char>>(arr[i], word[i]);
        Transmitter sender;
        sender.Send(chunk, 0, 0);
    }
}

void Thread4()
{
    std::string word = "QW"; 
    int arr[] = {33000,170000}; 
    for(int i = 0; i < word.size();  ++i)
    {
        auto chunk = std::make_shared<std::vector<char>>(arr[i], word[i]);
        Transmitter sender;
        sender.Send(chunk, 111, 1);
    }
}   


int main(int argc, char *argv[])
{
    size_t param = atoi(argv[1]);
    std::thread t1(Thread1, param);
    // std::thread t2(Thread2);
    std::thread t3(Thread3);
    std::thread t4(Thread4);

    sleep(1);

    t1.join();
    // t2.join();
    t3.join();
    t4.join();

    return 0;
}

