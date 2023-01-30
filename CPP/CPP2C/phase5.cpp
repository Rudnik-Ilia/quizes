#include <iostream>
#include <stdio.h>

using namespace std;

class Point
{
    public:
        Point(int x, int y);
    private:
        int m_x;
        int m_y;
};

Point::Point(int x, int y): m_x(x), m_y(y)
{

}

class A
{

};

class B
{
    private:
        int x;
        int y;
        Point p;
};


int main()
{
    A a;
    B b;
    B b2(b);
    b2 = b; 

    return 0;
}