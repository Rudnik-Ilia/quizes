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
   
        cout << "Thread Run NORMAL" << endl;  
        
    }

};
class MyTaskHigh: public ITask
{
    public:
    void Execute()
    {
    
        cout << "Thread Run HIGH" << endl;  
        
    }

};
class MyTaskLow: public ITask
{
    public:
    void Execute()
    {
        cout << "Thread Run LOW" << endl;  
        
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

    ThreadPool *pool = new ThreadPool(10);

    pool->AddTask(std::shared_ptr<MyTaskNormal>(new MyTaskNormal()), ThreadPool::PRIORITY_NORMAL);
    pool->AddTask(std::shared_ptr<MyTaskHigh>(new MyTaskHigh()), ThreadPool::PRIORITY_HIGH);
    pool->AddTask(std::shared_ptr<MyTaskLow>(new MyTaskLow()), ThreadPool::PRIORITY_LOW);

    sleep(3);
    

    return 0;
}