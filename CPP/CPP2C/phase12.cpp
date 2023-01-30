#include <iostream>

using namespace std;


class A
{
    public:
    int a;
    int Foo()
    {
        return 2;
    };

    A(): a(Foo())
    {

    };
    
};




int main()
{
    A a();
    return 0;
}
