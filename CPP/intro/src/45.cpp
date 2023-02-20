#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <utility>
#include <memory>
using namespace std;

// class Base
// {
//     virtual void Run()
//     {
//             cout << "Run Base" << endl;
//     }
// };

class A
{
    public:
   
    virtual void Run()
    {
            cout << "Run A" << endl;
    }

};

class B 
{
    public:

    virtual void Run()
    {
        cout << "Run B" << endl;
    }
};

class C: public A, B
{   
    public:
    virtual void Run()
    {
        B::Run();
    }
   
};


int main()
{
    // Base base;
    

    C c;
    c.Run();
    // b.a = 10;
    // b.b = 11;
    
    // c.Run();
    // b.Run();
    

    return 0;
}