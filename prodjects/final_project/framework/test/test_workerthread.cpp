#include <iostream>
using std::cout;
using std::endl;

#include "WorkerThread.hpp"
#include "ITask.hpp"
using namespace ilrd;

typedef std::function<std::shared_ptr<ITask>> f_task;

typedef std::shared_ptr<ITask> p_task;

class MyTask: public ITask
{
    public:
    void Execute()
    {
        cout << "Thread Run" << endl;
    }

    private:

};

std::shared_ptr<ITask> getTask()
{
    return std::shared_ptr<ITask>(new MyTask());
}

int main()
{
    MyTask my;
    std::shared_ptr<ITask> p_task(new MyTask);


    (getTask())->Execute();

    std::function<std::shared_ptr<ITask>()>  send_func = std::bind(getTask);


    

    // WorkerThread();

    return 0;
}