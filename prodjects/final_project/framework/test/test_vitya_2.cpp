#include <iostream>
#include <unistd.h>
#include <cstdio>

#include "ThreadPool.hpp"

using namespace ilrd;
using namespace std;

void Test1();
void Test2();
void Test3();

class MyTask : public ITask
{
public:
    MyTask(bool b_print_ = true) : m_print(b_print_) {}
    void Execute() override
    {
        char buff[100] = {0};
        if(m_print)
        {
            sprintf(buff, "%s%lu", "Custom task: ", std::this_thread::get_id());
            cout << buff << endl;
        }

    }

private:
    bool m_print;
};

int main()
{
    cout << "Test1" << endl;
    Test1();

    cout << "Test2" << endl;

    Test2();

    cout << "Test3" << endl;

    Test3();

    return 0;
}

void Test1()
{
    size_t pause_counter = 0;
    size_t counter = 20;
    
    while(counter)
    {
        ++pause_counter;
        {
        cout << "START" << endl;
        ThreadPool tp(20);

        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));
        tp.AddTask(shared_ptr<ITask>(new MyTask()));

        if(pause_counter >= 2)
        {
            tp.Resume();
            tp.Pause();
            sleep(1);
            tp.Pause();
            sleep(1);
            tp.Resume();
            pause_counter = 0;
            --counter;
        }
        }
        cout << "STOP" << endl;
        cout << "----------------" << endl;
        cout << "pause_counter " <<pause_counter << endl;

        cout << "counter " <<counter << endl;
    }
}

void Test2()
{
    size_t set_counter = 0;
    size_t counter = 20, counter2;
    bool is_set = false;
    
    while(--counter)
    {
        {
        cout << "START" << endl;
        ThreadPool tp(20);
        counter2 = 20;
        is_set = false;
        while(counter2)
        {
            ++set_counter;
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));

            if(set_counter >= 5)
            {   
                set_counter = 0;
                if(!is_set)
                {
                    tp.SetThreadNum(counter);
                    is_set = true;
                }
                --counter2;
            }
        }
        }
        cout << "STOP" << endl;
        //usleep(500);
    }

}

void Test3()
{
    size_t set_counter = 0;
    size_t counter = 15, counter2;
    bool is_set = false;
    
    while(--counter)
    {
        {
        cout << "START" << endl;
        ThreadPool tp(5);
        counter2 = 15;
        is_set = false;
        while(counter2)
        {
            ++set_counter;
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));
            tp.AddTask(shared_ptr<ITask>(new MyTask(false)));

            if(set_counter >= 5)
            {   
                set_counter = 0;
                if(!is_set)
                {
                    tp.SetThreadNum(5 + (15 - counter));
                    is_set = true;
                }
                --counter2;
            }
        }
        }
        cout << "STOP" << endl;
        //usleep(500);
    }  
}
