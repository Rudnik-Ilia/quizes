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
        X(double d_): m_a(d_)
        {
            cout << "X Ctor" << endl;
        }
        virtual ~X()
        {

        }
        int a;
    private:
        double m_a;
};
class Y: public X
{
    public:
        Y(double d_, int i_): X(d_) ,m_b(i_)
        {
             cout << "Y Ctor" << endl;
        }
        ~Y()
        {

        }
        int b;
    private:
        double m_b;
};

int main()
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    

    // X x(3.14);
    // char* ptr = (char*)&x;
    // cout << *((double*)(ptr+8)) << endl;
    // cout << *((int*)(ptr+16)) << endl;
    // cout << *((int*)(ptr+20)) << endl;
    // *((int*)(ptr+16)) = 111;
    // cout << *((int*)(ptr+16)) << endl;
    

    cout << &y1 << endl;
    cout << &y3 << endl;
    cout << "--------------" << endl;


    X& x1 = y1;
    X& x2 = y2;
    

    x1 = x2;
    
    y3 = y4;

    
    cout << &y1 << endl;
    cout << &y3 << endl;

    return 0;   
}


