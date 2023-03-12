#include <iostream>
using std::cout;
using std::endl;
using std::string;

#include "Factory.hpp"
#include "Singleton.hpp"
#include "ITask.hpp"

using namespace ilrd;


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

struct ArgsForWrite: public FactoryArgs
{
    ArgsForWrite(string &str, size_t num): m_str(str), m_num(num){} 

    string &m_str;
    size_t m_num;
};

std::shared_ptr<ITask> CreaterWrite(FactoryArgs &arguments)
{
    ArgsForWrite &args =  dynamic_cast<ArgsForWrite&>(arguments);
    return std::shared_ptr<WriteFunc>(new WriteFunc(args.m_str,args.m_num));
}

int main()
{

    string str1 = "Im reader";

    Factory<ITask, string> factor;
    




    return 0;
}