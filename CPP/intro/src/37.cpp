#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <utility>
#include <memory>
using namespace std;

// int Foo(int) throw(bad_alloc);
// int Bar() throw(bad_cast);
int Bar()
{
    throw runtime_error("ss");
    return 1;
}

int Foo(int x)
{   
    try
    {
        cout<< "Fooo" << endl;
        if(!uncaught_exception)
        {
            throw runtime_error("ss");
        }
    }
    catch(const std::exception& e)
    {
        cout <<  "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGgg" << endl;
        throw;
    }
    
     return 1;
}
class X
{
    public:
    X()
    {
        cout<< "Example Ctor" << endl;
    }
    ~X();
    int m_a;
};

X::~X() 
{
    // cout<< "Example Destor" << endl;
    // try
    // {
        cerr<< Foo(m_a) << endl;
    // }
    // catch(const std::exception& e)
    // {
    //     cout <<  "Ex FRON DESTRUCTOR" << endl;;
    // }
    
}

void Fishi()
{
    X x1;
    Bar();
    cout<< "Fishi" << endl;
}

int main()
{
    try
    {
        Fishi();
    }
    catch(...)
    {
        cout << "END" << endl;
    }
    
    return 0;
}
