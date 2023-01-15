#include <iostream>
using namespace std;




struct X
{
    // explicit X(); // initialization function without parametrs, is named default
    explicit X(int a_, int b_ = 8);//regular not default ctor
    ~X();//deinitialization fucntion is called destructor dtor
    X(const X& other_);//copy  initialization function is called copy constructor

    // X(char *x);//copy  initialization function is called copy constructor

    // X& operator = (const X& other_); //assignement operator 

    int m_a;
    const int m_b;

};

// X::X(): m_a(3), m_b(4)//, m_b(4) //impelementatiuon default ctor// list of inizialize for constant int
// {
//     // m_a = 3;
//     // m_b = 4;
//     std::cout << "this:" << this << "X default Ctor. m_a:" << m_a<< "m_b:" << m_b << std::endl;

// }

X::X(int a_, int b_) : m_a(a_), m_b(b_) // implement second ctor
{
    std::cout << "this:" << this << "X int int Ctor. m_a:" << m_a << 
    "m_b:" << m_b << std::endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b)// copy ctor
{
    std::cout << "this:" << this << "X copy Ctor. m_a:" << m_a << 
    "m_b:" << m_b << std::endl;
}


// X& X::operator = (const X& other_)
// {
//     m_a = other_.m_a;
//     // m_b = other_.m_b;
//     std::cout << "this:" << this << 
//     "X assigment operator. m_a:" << m_a << 
//     "does not change m_b:" << m_b << std::endl;
//     return *this;
// }

X::~X()
{
    std::cout << "this:" << this << "X Dtor. m_a:" << m_a <<
    "m_b:" << m_b << std::endl;
}
struct Y
{
    Y();
    X m_x;
    int m_i;

};

Y::Y(): m_x(1), m_i(2)
{

}

int main()
{
    // X x1();
    


    X x2(7);

    X *px = new X(x2);

    X x3(9, 10);


    X x4(x3);
    

    Y y1;
    

    

    cout << "---------------" << endl;
    y1.m_x.m_a = 250;
    // y1.m_x.m_b = 750;
    cout << "---------------" << endl;

    // Y y2(&y1);
    cout << "---------------" << endl;
    Y y3();
    cout << "---------------" << endl;

    // y3 = y1;
    



    // X* xp = new X[10];
    // double* xp = new double[10];


   
    
    // delete px;
   
    // px = 0;

    
    return 0;
    
}


