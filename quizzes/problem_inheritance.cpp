#include <iostream>

#include <iostream>

using namespace std;

struct Base
{
    Base() {cout << "Base ctor" << endl;}
    virtual ~Base() {cout << "Base dttor" << endl;}
    Base(const Base&) {cout << "Base cctor" << endl;}
    virtual void operator=(const Base&) {cout << "Base = " << endl;}
    virtual void print(){cout << "Base print" << endl;}
};

struct Derived: public Base{
    Derived(){cout <<"Derived ctor" << endl;}
    ~Derived(){cout << "Der dtor" << endl;}
    virtual void operator=(const Derived&) {cout << "Derived" << endl;}
    virtual void print(){cout << "derived print "<< endl;}
};

void Print(Base& p)
{
    p.print();
}

int main()
{
    Base b;
    cout<<"1----------------"<<endl;
    Base *pb = new Derived;
    cout<<"2----------------"<<endl;
    Print(b);
    cout<<"3----------------"<<endl;
    Print(*pb);
    cout<<"4----------------"<<endl;
    pb->print();
    cout<<"5----------------"<<endl;
    delete pb;
    return 0;
}