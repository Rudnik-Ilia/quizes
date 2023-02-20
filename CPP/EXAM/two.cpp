#include <iostream>
using namespace std;


class A
{
    public:
    A(){}
    virtual void Foo()
    {
        cout << "Foo AAA" << endl;
    }
};

class B: public A
{
    public:
    B(){}
    void Foo()
    {
        cout << "Foo BBB" << endl;
    }
};

void Bar(A& x)
{
    x.Foo();
}

void Foo() try 
{
    cout << "EXEPT" << endl;
    throw 1;
}
catch(...)
    {
        cout << "!!!!!!!!!" << endl;
    }

int main()
{

    // B b;
    // b.Foo();
    // A& a = b;

    // A* aa = new B();

    // a.Foo();

    // aa->Foo();

    // // Bar(b);
    // // Bar(a);

    // Bar(b);
    Foo();
    
    



    return 0;
}