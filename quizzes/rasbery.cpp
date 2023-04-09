#include <iostream>
using namespace std; 


class A
{
    public:
    A(){};
    A(const A& a)
    {
        cout << "CCtor" << endl;
    }
    void Foo()
    {
        cout << "CCtor" << endl;
    }

};
class B: public A
{
    public:
    B(){};
   
    void Foo()
    {
        // static_cast<A>(*this).Foo();
        A*(this)->Foo();
        cout << "CCtor+++++" << endl;
    }

};




int main()
{
   B b;
   b.Foo();
}