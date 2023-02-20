#include <iostream>
using namespace std;

void Foo(const double& x)
{
    cout << &x << endl;
}
void Faa(double& x)
{
    cout << &x << endl;
}

int main()
{
    int i; 
    
    Faa(i);



    return 0;
}