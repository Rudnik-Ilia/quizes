#include <iostream>
using namespace std;

void Foo(const double& x)
{
    cout << x << endl;
    cout << &x << endl;
}
void Faa(double& x)
{
    cout << x << endl;
    cout << &x << endl;
}

int main()
{
    int i = 99; 
    // int& f = 300;

    // Foo(i);
    
    Faa(i);


    return 0;
}