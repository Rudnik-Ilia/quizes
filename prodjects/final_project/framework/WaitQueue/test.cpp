#include <iostream>
#include <queue>
#include <chrono>
#include <thread>

#include "waitqueue.hpp"


using namespace ilrd;
using namespace std;


template <typename T, typename CONTAINER>
void producer_do( WaitableQueue<T, CONTAINER>& q, int start)
{
    std::string msg[10];
    for(int i = 0; i < 10; ++i)
    {
        msg[i] = "msg" + to_string(start + i);
    }
    
    for(int i = 0; i < 10; ++i)
    {
        q.Push(msg[i]);
    }
}

template <typename T, typename CONTAINER>
void consumer_do( WaitableQueue<T, CONTAINER>& q, int i)
{
    T var;
    T def;
    std::chrono::milliseconds timeout(1000);
    while(1)
    {
        q.Pop(timeout, var);
        cout << "thread: "<< i << " " << var << endl;
        var  = def;
    }
}

int main()
{
    std::string str;
    std::chrono::milliseconds timeout(000);
    WaitableQueue<std::string, std::queue<std::string>> q;

    std::thread producer(producer_do<std::string, std::queue<std::string>>, std::ref(q), 0 );
    std::thread producer_2(producer_do<std::string, std::queue<std::string>>, std::ref(q), 10 );

    std::thread consumer_1(consumer_do<std::string, std::queue<std::string>>, std::ref(q), 1 );
    std::thread consumer_2(consumer_do<std::string, std::queue<std::string>>, std::ref(q), 2 );


    producer.join();
    producer_2.join();

    consumer_1.join();
    consumer_2.join();


    return 0;
}
