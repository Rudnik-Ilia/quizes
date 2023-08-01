#include <iostream>
#include <unistd.h>


class A
{
    public:
    A()
    {

    }
    void Run()
    {
        std::cout << "Run A" << '\n';
    }

};

class B: public A
{
    public:
        B(){}
    void Run()
    {
        std::cout << "Run B" << '\n';
    }
};

void Foo(B& cl)
{
    cl.Run();
}



int main()
{

    // A* a = new B;
    // B* b = new B;

    A a;
    B b;

    Foo(a);
    Foo(b);

  
    return 0;
}