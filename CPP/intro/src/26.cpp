#include <iostream>
#include <cstdio>
using namespace std;

class X
{
    public:
        explicit X(int a);
        void Foo();
        int Get() const;

    // private:
        int m_a;

};

X::X(int a): m_a(a)
{

}

void X::Foo()
{
    printf("%d\n", m_a);
}
int X::Get() const
{
    return m_a;
}

void Foo(const X& x)
{
    // printf("%d", x.m_a);
    printf("%d\n", x.Get());
}





int main()
{
    X x1(77);
    // X x2 = 88;

    x1.Foo();
    printf("%d\n", x1.Get());

    Foo(x1);

    return 0;
}