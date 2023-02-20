#include <iostream>

class X
{
    public:
        X():m_id(++s_cntr){}
        int GetId() 
        {
            std::cout << m_id << std::endl; 
            return m_id;
        }
        
        static int Foo(X& x)
        {
            return x.m_id;
        }

        void Bar(X& x)
        {
            Foo(x);
        }
    private:
        static int s_cntr;
        int m_id;
};

int X::s_cntr = 0;



int main()
{
    X x1;
    X x2;
    X x3;
    x1.GetId();
    x2.GetId();
    x3.GetId();

    x3.Bar(X());
    
    

    return 0;
}