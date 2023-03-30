
#include <unistd.h>
#include "Asyncinjection.hpp"

using namespace ilrd;

class Functor
{
    public:
        Functor(int x): count(x){}

        bool operator()()
        {
            std::cout << "MINUS" << std::endl;
            if(--count)
            {
                return true;
            }
            return false;
        }
    private:
        int count;
};

bool Foo()
{
    std::cout << "TRUE FOO" << std::endl;
    return true;
}

bool Bar()
{
    std::cout << "FALSE BAR" << std::endl;
    return false;
}

int main() 
{ 
    auto m_interval_1 = std::chrono::milliseconds(1000);
    auto m_interval_3 = std::chrono::milliseconds(3000);
    auto m_interval_5 = std::chrono::milliseconds(5000);

    // new AsyncInjection(Bar, std::chrono::milliseconds(m_interval_1));
    // new AsyncInjection(Foo, std::chrono::milliseconds(m_interval_3));
    // new AsyncInjection(Bar, std::chrono::milliseconds(m_interval_5));

    Functor func(7);

    AsyncInjection *inj_1 = new AsyncInjection(func, std::chrono::milliseconds(m_interval_3));
    AsyncInjection *inj_2 = new AsyncInjection(Foo, std::chrono::milliseconds(m_interval_1));

    sleep(20);

    return 0;

}