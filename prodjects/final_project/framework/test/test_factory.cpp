#include <iostream>
using std::cout;
using std::endl;
using std::string;


#include "Factory.hpp"
#include "ITask.hpp"

using namespace ilrd;

class ReadFunc: public ITask
{
    public:
        ReadFunc(string &str): m_str(str){}
        void Execute()
        {
            cout << m_str << endl;
        }

    private:
        string &m_str;
};

class WriteFunc: public ITask
{
    public:
        WriteFunc(string &str, size_t num): m_str(str), m_num(num){}
        void Execute()
        {
            cout << m_str << '+' << m_num << ' ' << endl;
        }

    private:
        string &m_str;
        size_t m_num;
};


struct ArgsForRead: public FactoryArgs
{
    ArgsForRead(string &str): m_str(str){}

    string &m_str;
};

struct ArgsForWrite: public FactoryArgs
{
    ArgsForWrite(string &str, size_t num): m_str(str), m_num(num){} 

    string &m_str;
    size_t m_num;
};

std::shared_ptr<ITask> CreaterRead(FactoryArgs &arguments)
{   
    ArgsForRead &args =  dynamic_cast<ArgsForRead&>(arguments);
    return std::shared_ptr<ReadFunc>(new ReadFunc(args.m_str));
}

std::shared_ptr<ITask> CreaterWrite(FactoryArgs &arguments)
{
    ArgsForWrite &args =  dynamic_cast<ArgsForWrite&>(arguments);
    return std::shared_ptr<WriteFunc>(new WriteFunc(args.m_str,args.m_num));
}




int main()
{   
    string str1 = "Im reader";
    string str2 = "Im writer";
    
    ArgsForRead reader(str1);
    ArgsForWrite writer(str2, 555);

    Factory<ITask, string> factor;

    factor.Register("R", CreaterRead);
    factor.Register("W", CreaterWrite);


    factor.Create("R", reader)->Execute();
    factor.Create("W", writer)->Execute();



    return 0;
}