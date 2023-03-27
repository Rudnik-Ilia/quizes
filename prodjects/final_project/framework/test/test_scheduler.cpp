#include <unistd.h>

#include "Scheduler.hpp"
#include "ITask.hpp"

using namespace ilrd;

class MyTaskNormal: public ITask
{
    public:
    void Execute()
    {
        for(int i = 0; i < 3; ++i)
        {
            std::cout << "Thread Run NORMAL" << std::endl; 
            sleep(1);    
        }  
    }
};

class MyTaskLow: public ITask
{
    public:
    void Execute()
    {
        for(int i = 0; i < 3; ++i)
        {
            std::cout << "Thread Run LOW" << std::endl; 
            sleep(1);    
        }
    }
};

class MyTaskHigh: public ITask
{
    public:
    void Execute()
    {
        for(int i = 0; i < 3; ++i)
        {
            std::cout << "Thread Run HIGH" << std::endl; 
            sleep(1);    
        } 
    }
};


int main()
{
    auto m_interval = std::chrono::milliseconds(2000000000);

    Scheduler* sched = Singleton<Scheduler>::GetInstance();

    sched->AddTask(std::shared_ptr<MyTaskNormal>(new MyTaskNormal()), m_interval);
    sched->AddTask(std::shared_ptr<MyTaskLow>(new MyTaskLow()), m_interval);
    sched->AddTask(std::shared_ptr<MyTaskHigh>(new MyTaskHigh()), m_interval);


    sleep(15);

    return 0;
}