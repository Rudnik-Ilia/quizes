#include <iostream>
using std::cout;
using std::endl;

#include "Dispatcher.hpp"

using namespace ilrd;

void Foo(const int &x, const int &y)
{
    cout << "SUMM: "<< x + y << endl;
}

void Bar(const int &x, const int &y)
{
    cout << "DIV: "<< x - y << endl;
}



int main()
{
    Dispatcher<int, int> disp;

    std::function<void(const int&, const int&)> wrap1 = Foo;
    std::function<void(const int&, const int&)> wrap2 = Bar;

    disp.Subscribe(Callback<int, int>(wrap1));
    disp.Subscribe(Callback<int, int>(wrap2));

    disp.Dispatch(10,9);

    return 0;
}
