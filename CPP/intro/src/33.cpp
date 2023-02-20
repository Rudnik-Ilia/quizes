#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
// alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
using namespace std;

class X
{
    public:
    X()
    {
        cout<< "Example Ctor" << endl;
    }
    ~X()
    {
        cout<< "Example Destor" << endl;
    }

};




struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog") : runtime_error(s_)
    {
        cout << "Bad dog ctor" << endl;
    }
};

struct Mistake: public logic_error
{
    
        Mistake(const string& s_ = "My mistake") : logic_error(s_)
        {
            cout << "My mistake ctor" << endl;
        }
        ~Mistake() throw()
        {
            cout << "My mistake DESTRUCT" << endl;
        }
};
void Fifi()
{
    throw BadDog("bad pup");
    // throw Mistake("XAXAXA");
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    X x1;
    Fifi();
    cerr << "Foo after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

int main()
{
    try 
    {
        Bar();
    }
    catch(BadDog& b)
    {
        cerr << "Bad dog exception:" << b.what(); 
        exit(3);
    }
    catch(Mistake b)
    {
        cerr << "PISEC" << b.what(); 
    
        exit(3);
    }
    catch(bad_alloc&)
    {
        cerr << "Out of memory! exiting.";
        exit(2);
    }
    catch(exception& r)
    {
        cerr << "unknown exception:" << r.what();
        exit(4);
    }

    cout << "CONEC" << endl;
    return 0;
}