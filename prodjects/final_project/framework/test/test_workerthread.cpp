#include <iostream>
using std::cout;
using std::endl;

#include <unistd.h>

#include "WorkerThread.hpp"
#include "ITask.hpp"
#include "ThreadPool.hpp"
using namespace ilrd;


class MyTask: public ITask
{
    public:
    void Execute()
    {
            cout << "Thread Run" << endl;  
    }

};

std::shared_ptr<ITask> getTask()
{
    return std::shared_ptr<ITask>(new MyTask());
}

int main()
{
    std::function<std::shared_ptr<ITask>()> send_func = std::bind(getTask);

    // send_func().get()->Execute();

    WorkerThread *work = new WorkerThread(send_func);
    sleep(1);

    return 0;
}