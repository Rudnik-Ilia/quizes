#include <iostream>
using namespace std;




struct X
{
    X(int a, int b);

    void Inc();
    void Dec();
    void Deca();

    int m_a;
    int m_b;

    // double z;
};

X::X(int a, int b): m_a(a), m_b(b) 
{}

void X::Inc()
{
    ++m_a;
    ++m_b;
    cout << this << endl;
}
void X::Dec()
{
    --m_a;
    --m_b;
    cout << this << endl;
}
void X::Deca()
{
    --m_a;
    --m_b;
    cout << this << endl;
}


void Inc()
{
    cout << "VOID" << endl;
}

int main()
{
    X x1(7, 55);
    X x2(x1);
    cout << &x1 << endl;
    cout << &x2 << endl;



    Inc();

    x1.Inc();
    x1.Inc();
    x2.Dec();


    cout << x1.m_a << ' ' << x1.m_b << endl;
    cout << x2.m_a << ' ' << x2.m_b << endl;

    
   
    // cout << sizeof(x1) << endl;
    // cout << sizeof(x2) << endl;


    
    return 0;
}