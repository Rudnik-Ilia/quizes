#include <iostream>
// #include <wrappqueue.hpp>
#include <future>
#include <unistd.h>
#include <functional>
using namespace std;

int Some()
{
    cout << "Some" << endl;
    return 1;
}

int Plus(int a, int b, string str)
{
    cout << str <<  a + b << endl;

    return a + b;
}
void ModArray(int * arr, int size)
{
    for(int i = 0; i < size; ++i)
    {
        arr[i] = arr[i] * 2;
    }
}

class A
{
    public:
    A(){};
    A(const A& a)
    {
        cout << "Coppppppy" << endl;
    };
};

void Faa(A &x)
{
    cout << "Faaaa" << endl;
}

struct func
{
    int operator()()
    {
         cout << "Functor!" << endl;
         return 0;
    }
};

int main()
{
    std::future<int> my_f = async([](){
        sleep(5);
        cout<< "Inside..." << endl;
        return 50;
    });
    // std::future<int> my_f = async(Some);
   
    
    cout<< my_f.get() << endl;

    cout<< "Some after actions..." << endl;

    // Plus(9, 8, "ILIA");

    // auto foo = bind(Plus, placeholders::_1, placeholders::_2, placeholders::_5);
    // foo(1,2,3,4, "ilia", "rudnik");

    // int arr[] = {3,4,5};

    // // ModArray(arr, 3);

    // A a;

    // A& s = a;

    // auto varr = bind(ModArray, ref(arr), placeholders::_2);

    // varr(arr, 3);

    // for(int i = 0; i < 3; ++i)
    // {
    //     cout<< arr[i] << ' ';
    // }
    // cout << '\n';

    // auto faa = bind(Faa, ref(a)) ;

    // faa(s);

    // func f;

    // auto fun = bind<int>(f)();

   

    


    return 0;
}