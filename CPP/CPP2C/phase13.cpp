#include <iostream>
using namespace std;

class A
{
    public:
        virtual ~A()
        {

        }
        virtual void Foo()
        {
            cout<<"Foo"<<endl;
        }
};

class B: public A
{

};

class C {
    public:
    C()
    {
        std::cout << "CTOR.\n";
    };
    C(const C&) 
    { 
        std::cout << "A copy was made.\n"; 
    }

};

C Foo() 
{
    C c;
    return c;
}

int main()
{
    // B b();
    
    std::cout << "Hello World!\n";
    C obj = Foo();
}