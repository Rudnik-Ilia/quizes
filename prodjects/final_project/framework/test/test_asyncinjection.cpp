
#include <unistd.h>
#include "Asyncinjection.hpp"

using namespace ilrd;

class Functor
{
    public: 
        bool operator()()
        {
            std::cout << "BOOL" << std::endl;
            return true;
        }
};

bool Foo()
{
    std::cout << "BOOL FOO" << std::endl;
    return true;
}

bool Bar()
{
    std::cout << "BOOL BAR" << std::endl;
    return false;
}

int main()
{
    auto m_interval_3 = std::chrono::milliseconds(3000);

    // new AsyncInjection(Foo, std::chrono::milliseconds(m_interval_3));
    new AsyncInjection(Bar, std::chrono::milliseconds(m_interval_3));

    sleep(10);

    return 0;

}