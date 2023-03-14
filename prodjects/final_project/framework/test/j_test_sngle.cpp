#include <iostream>

#include "Factory.hpp"
#include "ITask.hpp"
#include "Singleton.hpp"

using namespace ilrd;
using namespace std;

class ReadTask : public ITask
{
public:
    ReadTask(const std::string &str) : m_str(str) {}
    void Execute() override { cout << m_str << endl; }

private:
    const std::string &m_str;
};

class WriteTask : public ITask
{
public:
    WriteTask(std::string &str, int task_num) : m_str(str), m_task_num(task_num)
    {
    }
    void Execute() override { m_str += to_string(m_task_num) + " "; }

private:
    std::string &m_str;
    int m_task_num;
};

struct ReadArgs : public FactoryArgs
{
    ReadArgs(const std::string &str_) : str(str_) {}
    const std::string &str;
};

std::shared_ptr<ITask> CreateReadTask(FactoryArgs &a)
{
    return std::move(std::shared_ptr<ReadTask>(
        new ReadTask((dynamic_cast<ReadArgs &>(a)).str)));
}

struct WriteArgs : public FactoryArgs
{
    WriteArgs(std::string &str_) : str(str_) {}
    std::string &str;
    int task_num;
};

std::shared_ptr<ITask> CreateWriteTask(FactoryArgs &a)
{
    WriteArgs &wa = dynamic_cast<WriteArgs &>(a);
    return std::move(
        std::shared_ptr<WriteTask>(new WriteTask(wa.str, wa.task_num)));
}

int main()
{
    std::string str;
    ReadArgs ra(str);
    WriteArgs wa1(str);
    WriteArgs wa2(str);
    wa1.task_num = 2;
    wa2.task_num = 5;

    Factory<ITask, std::string> *fa =
        Singleton<Factory<ITask, std::string>>::GetInstance();
    Factory<ITask, std::string> *fa2 =
        Singleton<Factory<ITask, std::string>>::GetInstance();

    fa->Register("READ", CreateReadTask);
    fa2->Register("WRITE", CreateWriteTask);

    auto r1 = fa->Create("READ", ra);
    auto r2 = fa2->Create("READ", ra);
    auto w1 = fa2->Create("WRITE", wa1);
    auto w2 = fa->Create("WRITE", wa2);

    w1->Execute();
    w2->Execute();
    r1->Execute();
    r2->Execute();

    return 0;
}
