#include <iostream>

class A
{
    public:
        A(int x);
        int a;
};
A::A(int x): a(x){}

class X
{
    public:
        explicit X();
        explicit X(int a_);
        explicit X(int a_, int b_);

        operator int() const;
        void Print() const;

    private:
       int m_a;
    //    int m_b;
};

X::X() : m_a() {
    std::cout << "11111111111"<<  this <<std::endl;
}
X::X(int a_) : m_a(a_){
    std::cout << "2222222222" << this << std::endl;
}
X::X(int a_, int b_) : m_a(a_ +  b_){
    std::cout << "333333333" << this << std::endl;
}

X::operator int()const
{
    return m_a;
}

void X::Print() const
{
    std::cout << "X::Print()" << m_a << std::endl;
}

void Fifi(const X& x_)
{
    std::cout << "Fifi()" << x_ << std::endl;
    x_.Print();
    // X* tmp = &x_;
    // std::cout << "Fifi()" << *tmp << std::endl;
    // tmp->Print();
    // std::cout << "Fifi()" << *(tmp+1) << std::endl;
    // (tmp+1)->Print();
    
}
void Foo(X x)
{
    std::cout << "!!!!" << std::endl;
}
void Foo(A a)
{
    std::cout << "????" << std::endl;
}


int main()
{
    // X(7);
    // X x();X::X(int a_) : m_a(a_){
//     std::cout << "2222222222" << this << std::endl;
// }
    // X x1 = X(0);
    // X x2 = X();
    
    // Fifi(X{7});

    
    X x1(7); 

    
    Fifi(x1); // 1

    Fifi(X(7)); // 2
    // Fifi(9); //3

    X x2(3,4);
    // Fifi(x2);
    Fifi(X(3, 4)); //4
    // Fifi(3, 4); //4
    return x1 * 3; //5

}