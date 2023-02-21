#include <iostream>
#include "shared.hpp"

using namespace ilrd;

typedef struct struct_test
{
    int x;
    int y;
    void print()
    {
        std::cout<<x<<" "<<y<<std::endl;
    }
}struct_test_t;

class Base
{
    public:
    Base(){}
    virtual ~Base(){}
    virtual void Foo() {std::cout << "I am a fool function inside Base Class" << std::endl;}
};

class Derived : public Base
{
    public:
    Derived(){}
    virtual ~Derived(){}
    virtual void Foo() {std::cout << "I am a fool function inside Derived Class" << std::endl;}
};

int main()
{
    SharedPointer<std::string> ptr1(new std::string("abobora"));
    std::cout << "after ptr1 (string type) - count = " << ptr1.UseCount() << std::endl;
    SharedPointer<std::string> ptr2(ptr1);
    std::cout << "after ptr2(ptr1) (string type) - count = " << ptr1.UseCount() << std::endl;
    std::cout << "ptr2 == ptr1 : " << (ptr2 == ptr1) << std::endl;
    ptr1.~SharedPointer();
    std::cout << "after ptr1 destruct - count: " << ptr2.UseCount() << std::endl;
    SharedPointer<int> ptr3(new int(123));
    std::cout << "after ptr3 (int type) - count: " << ptr3.UseCount() << std::endl;
    SharedPointer<int> ptr4;
    std::cout << "ptr3 value: " << *ptr3 << std::endl;
    std::cout << "ptr4 != ptr3 : " << (ptr4 != ptr3) << std::endl;
    std::cout << "after ptr4 (int type) - count: " << ptr4.UseCount() << std::endl;
    ptr4 = ptr3;
    std::cout << "after ptr4 = ptr3 (int type) - count: " << ptr4.UseCount() << std::endl;
    std::cout << "ptr4 value: " << *ptr4  << "stored in address: " << &ptr4 << std::endl;
    SharedPointer<int> ptr5;
    std::cout << "after ptr5 (int NULL) - count: " << ptr5.UseCount() << std::endl;
    SharedPointer<int> ptr6;
    std::cout << "after ptr6 (int NULL) - count: " << ptr6.UseCount() << std::endl;
    SharedPointer<struct_test_t> ptr7(new struct_test_t);
    ptr7->x = 10;
    ptr7->y = 11;
    ptr7->print();
    std::cout << "after ptr6 (int NULL) - count: " << ptr7->x << std::endl;

    /* Exercise with Base and Derived class */
    SharedPointer<Base>shared_pointer(new Derived);

    shared_pointer->Foo();

    SharedPointer<Base>bsp;
    SharedPointer<Derived>dsp(new Derived);
    bsp = dsp;

    dsp->Foo();
    bsp->Foo();


    return 0;
}
