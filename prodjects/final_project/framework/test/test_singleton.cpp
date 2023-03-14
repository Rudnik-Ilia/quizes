#include <iostream>
using std::cout;
using std::endl;
using std::string;
#include <thread>
using std::thread;
#include <unistd.h>

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
            // ++WriteFunc::x;
            cout << m_str << ' '<< this << ' ' << endl;
        }

    private:
        string &m_str;
        static size_t x;

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

void CreatorSingleton(ArgsForWrite args)
{

    for(size_t i; i < 10; ++i)
    {
        factory_p* f = Singleton<factory_p>::GetInstance();
        f->Register("W", CreaterWrite);
        f->Create("W", args)->Execute();
        cout << f << endl;
    }
}

void CreatorSingleton2(ArgsForWrite args)
{

    for(size_t i; i < 10; ++i)
    {
        factory_p fac;
        fac.Register("W", CreaterWrite);
        fac.Create("W", args)->Execute();
        cout << &fac << endl;
    }
    
}


int main()
{
    string str = "Im reader";

    ArgsForWrite writer(str);

    factory_p fac;
    factory_p fac2;

    factory_p* ptr2 =  Singleton<factory_p>::GetInstance();
    factory_p* ptr3 =  Singleton<factory_p>::GetInstance();

    cout << &fac << ' ' << &fac2 << endl;
    cout << ptr2 << ' ' << ptr3 << endl;

    fac.Register("W", CreaterWrite);
    fac2.Register("W", CreaterWrite);

    ptr2->Register("W", CreaterWrite);
    ptr3->Register("W", CreaterWrite);

    fac.Create("W", writer)->Execute();
    fac2.Create("W", writer)->Execute();

    ptr2->Create("W", writer)->Execute();
    ptr3->Create("W", writer)->Execute();
    
    thread t1(&CreatorSingleton, writer);
    thread t2(&CreatorSingleton2, writer);

    sleep(5);

    t1.join();
    t2.join();


    return 0;
}