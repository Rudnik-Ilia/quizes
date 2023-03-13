#include <iostream>
using std::cout;
using std::endl;
using std::string;
#include <thread>
using std::thread;

#include "Factory.hpp"
#include "Singleton.hpp"
#include "ITask.hpp"

using namespace ilrd;

typedef Factory<ITask, string> factory_p;

class WriteFunc: public ITask
{
    public:
        WriteFunc(string &str): m_str(str){}
        void Execute()
        {
            cout << m_str << endl;
        }

    private:
        string &m_str;
};

struct ArgsForWrite: public FactoryArgs
{
    ArgsForWrite(string &str): m_str(str){} 

    string &m_str;
};

std::shared_ptr<ITask> CreaterWrite(FactoryArgs &arguments)
{
    ArgsForWrite &args =  dynamic_cast<ArgsForWrite&>(arguments);
    return std::shared_ptr<WriteFunc>(new WriteFunc(args.m_str));
}

void CreatorSingleton()
{
    
}


int main()
{
    string str = "Im reader";

    ArgsForWrite writer(str);

    auto ptr1 = new factory_p();
    auto ptr4 = new factory_p();

    factory_p* ptr2 =  Singleton<factory_p>::GetInstance();
    factory_p* ptr3 =  Singleton<factory_p>::GetInstance();

    cout << ptr1 << ' ' << ptr4 << endl;
    cout << ptr2 << ' ' << ptr3 << endl;

    ptr1->Register("W", CreaterWrite);
    ptr2->Register("W", CreaterWrite);
    ptr3->Register("W", CreaterWrite);
    ptr4->Register("W", CreaterWrite);

    ptr1->Create("W", writer)->Execute();
    ptr2->Create("W", writer)->Execute();
    ptr3->Create("W", writer)->Execute();
    ptr4->Create("W", writer)->Execute();
    
    thread t1();
    thread t2();



    return 0;
}