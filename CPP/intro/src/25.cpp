#include <iostream>
using namespace std;

struct X
{
   explicit X(int a);
   ~X();

    void Foo();
    void Bar() const;

    int m_a;
    int *m_p;
  
};

X::X(int a): m_a(a), m_p(new int(a))
{}
X::~X()
{
    delete m_p;
    m_p = 0;
}
void X::Foo()
{
    ++m_a;
    --(*m_p);
}
void X::Bar() const
{
    cout << m_a << endl;
    cout << *m_p << endl;
    cout << m_p << endl;
    // m_a = 0;
    // m_p = 0;
    *m_p = 888;
    // Foo();


}

void Fifi(const X& x)
{
    // x.Foo();
    x.Bar();
}

int main()
{

    X x1(1);

    x1.Foo();
    // x1.Bar();
    Fifi(x1);
    Fifi(x1);





    return 0;
}