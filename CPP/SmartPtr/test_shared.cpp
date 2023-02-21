#include <iostream>
using std::cout;
using std::endl;

#include "shared.hpp"
using namespace ilrd;

class Base
{
    public:
        Base(int size)
        {
            memory = ::operator new(size);
        }
        ~Base()
        {
            ::operator delete(memory);
            cout << "Dtor BASE" << endl;
        }

    private:
        void *memory;
};

class Derived: public Base
{
    public:
        Derived(int size): Base(size)
        {

        }
        ~Derived()
        {
            cout << "Dtor DERIVED" << endl;
        }

    private:
        int x;

};
class Some
{   
    public:
        Some(int s): y(s){}
        ~Some()
        {
            cout << "Dtor SOME" << endl;
        }


    private:
        int y;

};

int main()
{
    SharedPointer<int> ptr1(new int(10));
    SharedPointer<float> ptr3(new float(3.14));

    {
        SharedPointer<int> ptr2(ptr1);
        cout << *(ptr1.GetPtr()) << endl;
        cout << "m_counter: " << ptr1.UseCount() << endl;
        cout << "m_counter: " << ptr2.UseCount() << endl;
        cout << "m_counter: " << ptr3.UseCount() << endl;
    }

    SharedPointer<Base> ptr6(new Base(10));
    SharedPointer<Derived> ptr4(new Derived(10));
    // SharedPointer<Base> ptr5(new Derived(10));

    ptr6 = ptr4;


    SharedPointer<Some> ptr7(new Some(7));

    // ptr6 = ptr7;

    ptr6 = ptr6;

    
    





    return 0;
}