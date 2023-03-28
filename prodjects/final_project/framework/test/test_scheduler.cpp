#include <unistd.h>

#include "Scheduler.hpp"
#include "ITask.hpp"
// gp11 test_scheduler.cpp -I ../include -lrt
using namespace ilrd;

class MyTaskNormal: public ITask
{
    public:
    void Execute()
    {
        std::cout << "Thread Run NORMAL" << std::endl; 
    }
};

class MyTaskLow: public ITask
{
    public:
    void Execute()
    {

        std::cout << "Thread Run LOW" << std::endl; 

    }
};

class MyTaskHigh: public ITask
{
    public:
    void Execute()
    {
        std::cout << "Thread Run HIGH" << std::endl; 
    }
};


int main()
{
    auto m_interval_1 = std::chrono::milliseconds(1000);
    auto m_interval_2 = std::chrono::milliseconds(2000);
    auto m_interval_3 = std::chrono::milliseconds(3000);
    auto m_interval_5 = std::chrono::milliseconds(5000);
    auto m_interval_10 = std::chrono::milliseconds(10000);
    auto m_interval_15 = std::chrono::milliseconds(15000);
    auto m_interval_20 = std::chrono::milliseconds(20000);

    Scheduler* sched = Singleton<Scheduler>::GetInstance();


    // sched->AddTask(std::shared_ptr<MyTaskLow>(new MyTaskLow()), m_interval_5);

    // sched->AddTask(std::shared_ptr<MyTaskHigh>(new MyTaskHigh()), m_interval_3);

    sched->AddTask(std::shared_ptr<MyTaskNormal>(new MyTaskNormal()), m_interval_1); 
    sched->AddTask(std::shared_ptr<MyTaskHigh>(new MyTaskHigh()), m_interval_10);

    sleep(20);

    return 0;
}