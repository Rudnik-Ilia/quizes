#include <iostream>
using std::cout;
using std::endl;

#include <unistd.h>

#include "WorkerThread.hpp"
#include "ITask.hpp"
#include "ThreadPool.hpp"

using namespace ilrd;


class MyTaskNormal: public ITask
{
    public:
    void Execute()
    {
   
        for(int i = 0; i < 3; ++i)
        {
            cout << "Thread Run NORMAL" << endl; 
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
            cout << "Thread Run HIGH" << endl; 
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
            cout << "Thread Run LOW" << endl;
            sleep(1);    
        }

    }

};
class MySleep: public ITask
{
    public:
    void Execute()
    {
        sleep(5);
    }

};

std::shared_ptr<ITask> getTask()
{
    return std::shared_ptr<ITask>(new MyTaskNormal());
}

int main()
{
    std::shared_ptr<MyTaskNormal>(new MyTaskNormal());
    std::function<std::shared_ptr<ITask>()> send_func = std::bind(getTask);

    // WorkerThread *work = new WorkerThread(send_func);

    ThreadPool *pool = new ThreadPool(1);

    pool->AddTask(std::shared_ptr<MySleep>(new MySleep()), ThreadPool::PRIORITY_HIGH);
    pool->AddTask(std::shared_ptr<MyTaskLow>(new MyTaskLow()), ThreadPool::PRIORITY_LOW);
    pool->AddTask(std::shared_ptr<MyTaskNormal>(new MyTaskNormal()), ThreadPool::PRIORITY_NORMAL);
    pool->AddTask(std::shared_ptr<MyTaskHigh>(new MyTaskHigh()), ThreadPool::PRIORITY_HIGH);

    sleep(16);
    

    return 0;
}