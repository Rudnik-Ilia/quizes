#include <unistd.h>
#include <iostream>
#include "Scheduler.hpp"
#include "ITask.hpp"

// gp11 test_scheduler.cpp ../src/Scheduler.cpp -I ../include -lrt

using namespace ilrd;

class MyTask: public ITask
{
    public:
    MyTask(int x): m_time(x){}
    void Execute()
    {
        std::cout << "Thread Run : " << m_time << std::endl; 
        // sleep(1);
    }
    int m_time;
};

int main()
{
    auto m_interval_1 = std::chrono::milliseconds(1000);
    auto m_interval_299 = std::chrono::milliseconds(2998);
    auto m_interval_2 = std::chrono::milliseconds(2000);
    auto m_interval_3 = std::chrono::milliseconds(3000);
    auto m_interval_333 = std::chrono::milliseconds(3002);
    auto m_interval_5 = std::chrono::milliseconds(5000);
    auto m_interval_10 = std::chrono::milliseconds(10000);
    auto m_interval_15 = std::chrono::milliseconds(15000);
    auto m_interval_20 = std::chrono::milliseconds(20000);

    Scheduler* sched = Singleton<Scheduler>::GetInstance();

    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(299)), m_interval_299);
    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(20)), m_interval_20);
    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(15)), m_interval_15);
    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(10)), m_interval_10);
    // sched->AddTask(std::shared_ptr<MyTask>(new MyTask(10)), m_interval_10); 
    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(5)), m_interval_5);

    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(3)), m_interval_3);

    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(2)), m_interval_2);
    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(1)), m_interval_1);
    sched->AddTask(std::shared_ptr<MyTask>(new MyTask(333)), m_interval_333);

    sleep(25);

    return 0;
}