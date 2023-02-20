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
    virtual ~X()
    {
        cout << "X Dtor" << this << endl;
    }
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
    ~Y()
    {
        cout << "Y Dtor" << this << endl;
    }
    private:
        int m_b;
};

void Foo()
{
    throw Y();
}

int main()
{

    


    X x1;
    Y y1;

    cout << sizeof(x1) << endl;
    cout << sizeof(y1) << endl;
   
    X *xp = new Y[5];


    // delete[] static_cast<Y*>(xp);
    delete[] xp;
   
    return 0;
}
