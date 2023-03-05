#include <iostream>
using std::cout;
using std::endl;
#include <thread>
using std::thread;
#include <unistd.h>

#include "wait_queue.hpp"

// gp11 test_waitqueue.cpp -lpthread  -I ../include

#define COLOR_RED "\033[1;31m" 
#define COLOR_BLUE "\033[1;34m" 
#define OFFCOLOR "\033[0m" 

using namespace ilrd;

WaitableQueue<int> mq1;

void Thread1()
{
    int x = 1;
    while(1)
    {
        cout << "PUT()  " << x << endl;
        mq1.Push(x++);
        sleep(1);
    }
   
}

void Thread2()
{
    int tmp = 0;

    while(1)
    {
        mq1.Pop(tmp);
        cout << "TAKE(1)  " << tmp << endl;
    }
}

void Thread2_1()
{
    int tmp = 0;

    while(1)
    {
        mq1.Pop(tmp);
        cout << "TAKE(2)  " << tmp << endl;
    }
}

void Thread3()
{
    int tmp = 0;
    std::chrono::milliseconds timeout(1000);

    while(1)
    {
        mq1.Pop(timeout, tmp);
        cout << "TAKE(3)  " << tmp << endl;
    }  
}

int main()
{
    thread t1(&Thread1);
    // thread t2(&Thread2);
    // thread t2_1(&Thread2_1);

    thread t3(&Thread3);

    t1.join(); 
    // t2.join(); 
    // t3.join();


    return 0;

}