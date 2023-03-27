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



int main()
{
    auto m_interval = std::chrono::milliseconds(1000);

    Scheduler* sched = Singleton<Scheduler>::GetInstance();

    sched->AddTask(std::shared_ptr<MyTaskNormal>(new MyTaskNormal()), m_interval);


    sleep(10);

    return 0;
}