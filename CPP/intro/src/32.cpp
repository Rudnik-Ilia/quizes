#include <iostream>
#include <cstdlib>
// #include <type_traits>
// #define OBJECT_HAS_VTABLE(T) (std::is_polymorphic<T>::value)


using namespace std;
class B
{
    public:
        B(){cout << "B::Ctor" << endl;}
        ~B() {cout << "B::Dtor" << endl;}
        virtual void Print1() const;
        virtual void Print2() const;
        virtual void Print3() const;
    private:
        int m_a;
};

void B::Print1() const
{
    cout << "B::Print1 B::m_a - " << m_a << endl; 
}
void B::Print2() const
{
    cout << "B::Print2!!!!!!!!!!!!!!!!!!!!q" << endl;
}

void B::Print3() const
{
    cout << "B::Print3" <<  endl;
}


class X: public B
{
    public: 
        X():m_b() {
            ss = new int[10];
            cout << "X::Ctor" << endl;}
        ~X(){
            delete[] ss;
            cout << "X::Dtor" << endl;}

        virtual void Print1() const
        {
            cout<< "X::Print1 X::m_b -" << m_b << endl;
            B::Print1();
            cout << "X::Print1 end" << endl;
        }

        void Print2() const {cout << "X::Print2" << endl;}

        int *ss = NULL; 
    private:
        
        int m_b;
};


int main()
{
    B *b1 = new B;
    B *b2 = new X;
 

    cout << "main b1:"<< sizeof(b1) << endl;
    cout << "main b2:" << sizeof(b2)<< endl;

    cout << endl << "main b1:" << endl;
    b1->Print1();
    b1->Print2();
    b1->Print3();
    
    
    cout << endl << "main b2: " << endl;
    b2->Print1();

    cout << "------------------------------------- " << endl;
    b2->Print2();
    cout << "------------------------------------- " << endl;
    b2->Print3();
    

    // X *xx = static_cast< X*>(b2);
    // cout << endl << "main xx:" << endl;
    // cout << "------------------------------------- " << endl;
    // xx->Print2();
    // cout << "------------------------------------- " << endl;
    // b2->Print2();

    delete b1;
    delete b2;
    return 0;
}