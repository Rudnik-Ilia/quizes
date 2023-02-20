#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <utility>
#include <memory>
using namespace std;


struct X
{   
    X()
    {
        cerr << "X Ctor"<< endl;
        throw runtime_error("sss");
    }
    X(int)
    {
        cerr << "X Ctor(int)"<< endl;
    }
    ~X()
    {
        cerr << "X DESCtor"<< endl;
    }
};
struct Y
{
    Y()
    {
        cerr << "Y Ctor"<< endl;
    }
    ~Y()
    {
        cerr << "Y DESCtor"<< endl;
    }
};

class L
{
    public:
    L(): m_x(2)
    {
        cerr << "L Ctor"<< endl;
    }
    ~L()
    {
        cerr << "L DESCtor"<< endl;
    }
    private:
        Y m_y;
        X m_x;

};

class M 
{
    public:
    M() 
    {
        cerr << "M Ctor"<< endl;
    }
    ~M()
    {
        cerr << "M DESCtor"<< endl;
    }
    private:
        Y m_y;
        X m_x;

};

class N 
{
    public:
    N()
    {
        cerr << "N Ctor"<< endl;
    }
    ~N()
    {
        cerr << "N DESCtor"<< endl;
    }
    private:
        Y m_y;
        X m_x;

};

class J 
{
    public:
    J(): m_y(new Y), m_x(new X)
    {
        cerr << "J Ctor"<< endl;
    }
    ~J()
    {
        cerr << "J DESCtor"<< endl;
        delete m_y;
        delete m_x;
    }
    private:
        Y *m_y;
        X *m_x;

};

class K 
{
    public:
    K()
    {
        cerr << "K Ctor"<< endl;
        m_y = new Y;
        m_x = new X;
    }
    ~K()
    {
        cerr << "K DESCtor"<< endl;
        delete m_y;
        delete m_x;
    }
    private:
        Y *m_y;
        X *m_x;

};

int main()
{
    // L var1;
    // M var2;
    // N var3;
    // J var4;
    // K var5;




    try
    {
        L var1;
        // M var2;
        // N var3;
        // J var4;
        // K var5;
    }
    catch(exception& e)
    {
        cerr << "exeption count. what:" << e.what() << '\n';
    }


    return 0;
}