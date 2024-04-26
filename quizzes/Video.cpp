#include <iostream>
#include <unistd.h>
#include <vector>
#include <yaml-cpp/yaml.h>


class A
{
    public:
    A(int x, int y): sss(x), ddd(y)
    {

    }
    void Foo(int var)
    {
        sss = var;
        std::cout << "from daddu" << sss << '\n';
    }
    virtual void Run()
    {
        std::cout << "Run A" << sss << '\n';
    }
    private:
        int sss;
        int ddd;

};

class B: public A
{
    public:
        B(int x, int y): A(x, y)
        {
            m_sss = x;
        }

    void Run()
    {
        std::cout << "Run B" << m_sss << '\n';
    }

    private:
        int m_sss;
};




int main() 
{

    B b(22, 33);
    b.Run();
    b.Foo(399);
  
    return 0;
}