#include <iostream>

using namespace std;
int main()
{
    int a = 7;
    int b = 8;
    int c = 9;
    int *ptr = &a;
    int *ptr1 = &b;
    int *ptr2 = &c;

    cout << ptr << endl;
    cout << *ptr << endl;
    cout << *ptr1 << endl;
    cout << *ptr2 << endl;

    *(reinterpret_cast<char*>(&ptr)) = 1;
    cout << ptr << endl;
    cout << *ptr << endl;
    return 0;

}