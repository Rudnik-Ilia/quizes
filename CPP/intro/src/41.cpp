#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <utility>
#include <memory>
using namespace std;


class X
{
    public:
    X()
    {
        cout << "X Ctor" << this << endl;
    }
    X(X& a)
    {
        cout << "X COPY Ctor" << this << endl;
    }
    virtual ~X()
    {
        cout << "X Dtor" << this << endl;
    }

    int a;
    private:
        double m_a;
};


class Y: public X
{
    public:
    Y()
    {
        cout << "Y Ctor" << this << endl;
    }
    Y(Y& a)
    {
        cout << "Y COPY Ctor" << this << endl;
    }
    ~Y()
    {
        cout << "Y Dtor" << this << endl;
    }
    int b;
    private:
        int m_b;
};

void Foo(X* x)
{
    // cout <<  << endl;
    cout << &(*x) << endl;
}


int main()
{

    Y y1;

    Y* p_y = &y1;
    cout << &y1 << endl;
    Foo(p_y);

    return 0;
}