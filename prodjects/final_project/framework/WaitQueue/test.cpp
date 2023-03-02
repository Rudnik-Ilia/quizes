#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
#include <unistd.h>

#include "waitqueue.hpp"


using namespace ilrd;
using namespace std;


template <typename T, typename CONTAINER>
void producer_do( WaitableQueue<T, CONTAINER>& q, int start)
{
    std::string msg[100];
    for(int i = 0; i < 100; ++i)
    {
        msg[i] = "msg" + to_string(start + i);

    }
    
    for(int i = 0; i < 100; ++i)
    {
        q.Push(msg[i]);
        sleep(1);
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

template <typename T, typename CONTAINER>
void consumer_do_no_timeout( WaitableQueue<T, CONTAINER>& q, int i)
{
    T var;
    T def;
    std::chrono::milliseconds timeout(1000);
    while(1)
    {
        q.Pop(var);
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
    // std::thread producer_2(producer_do<std::string, std::queue<std::string>>, std::ref(q), 10 );

    std::thread consumer_1(consumer_do<std::string, std::queue<std::string>>, std::ref(q), 1 );
    std::thread consumer_2(consumer_do<std::string, std::queue<std::string>>, std::ref(q), 2 );
    std::thread consumer_3(consumer_do<std::string, std::queue<std::string>>, std::ref(q), 3 );
    std::thread consumer_4(consumer_do_no_timeout<std::string, std::queue<std::string>>, std::ref(q), 4 );




    producer.join();
    // producer_2.join();

    consumer_1.join();
    consumer_2.join();
    consumer_3.join();
    consumer_4.join();




    return 0;
}
