#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class Point 
{
    public:
        // Point(): x(0), y(0)
        // {
        //     cout << "Default Ctor" << endl;
        // }
        Point(T x = 0 , T y = 0) : x(x), y(y)
        {
            cout << "Ctor" << endl;
        }
        Point(const Point<T> &other) : x(other.x), y(other.y) 
        {
            cout << "CCtor" << endl;
        }

        virtual ~Point(){}

        Point<T> operator+(const Point<T> &other) const 
        {
            return Point<T>(x + other.x, y + other.y);
        }

        Point<T> operator-(const Point<T> &other) const 
        {
            return Point<T>(x - other.x, y - other.y);
        }

        void operator+=(T num) 
        {
            this->x += num;
            this->y += num;;
        }

        void operator/=(T num)  
        {
            this->x /= num;
            this->y /= num;
        }

        bool operator==(const Point<T> &other) const
        {
            return x == other.x && y == other.y;
        }

        T x;
        T y;
};



int main()
{
    Point<int> p1(5,6);
    Point<int> p1_1(5,6);

    Point<int> p2(50,60);
    Point<int> p3(0,0);
    Point<int> p4;

    p4 = p1 + p2;

    Point<int> p5 = p1 - p4;

    assert(p1 == p1_1);

    Point<int> p6(p1);
    Point<int> p7(7,7);

    assert(p7 == Point<int>(7,7));
    
    p3+=1;
    p3/=2;

    Point<float> f1(2.3, 5.6);

    cout << f1.x << endl;
    


    return 0;
}





