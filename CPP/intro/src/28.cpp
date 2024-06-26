#include <iostream>
#include <cstdio>
using namespace std;


class X;
class Y;

int operator+(const X& x1_, const X& x2_)
{
    return 100;
}

// ostream& operator<<(ostream& os_, const X& x_);

class X
{
    public:
       
        bool operator == (const X& o_) const {return m_a == o_.m_a;}
    private:
        friend ostream& operator<<(ostream& os_, const X& x_);
        int m_a;
};


int main()
{
    X x1;
    X x2;
    cout<<"x1 + x2:" << x1 + x2 << "x1 == x2:" << (x1 == x2) <<" x1:" << &x1 << " x2:" << &x2 << endl;
    return 0;
}

ostream& operator<<(ostream& os_, const X& x_)
{
    return os_ << x_.m_a;
}

