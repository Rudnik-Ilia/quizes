#include <iostream>
#include <stdio.h>

using namespace std;



    class B
    {
        public:
        int x;
        int y;
    };

    union A
    {
        int a;
        int b;

        void Foo(){
            cout<< "Union" << endl;
        };
    };



int main()
{
    A b = {2};
    b.Foo();
    

   
    

    cout << b.a << endl;
    // cout << sizeof(B) << endl;
   

    return 0;
}