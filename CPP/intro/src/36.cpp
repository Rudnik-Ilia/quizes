#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <utility>
#include <memory>
using namespace std;



void Bar(int* x)
{
    cout<< "Bar" << endl;
}
void Fishi()
{
    cout<< "Fishi" << endl;
}
void Fifi(int* x)
{
    cout<< "Fifi" << endl;
    throw runtime_error("SASA");
}
void Dodo()
{
    cout<< "Dodo" << endl;
}

void Foo()
{
    int *ip = new int;                                   
    // // auto_ptr<int> ip(new int(15));
    // try
    // {
        Bar(ip);
        Fishi();
        Fifi(ip);
        Dodo();
    // }
    // catch(...)
    // {
    //     cout<< "CATCH!!!!" << endl;
    //     // std::cerr << e.what() << endl;
    // }

    // delete ip;
}



int main()
{
    try
    {
        Foo();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}