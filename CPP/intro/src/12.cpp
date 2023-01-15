#include <iostream>
#include <cstdlib>



namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_notthere;

    void Foo(){
        std::cout << "uselees foo" << std::endl;
    }

    namespace wasteoftyme
    {
        void Foo(){
            std::cout << "useless wasteoftime foo" << std::endl;
        }
    } //namespace wasteoftyme
}//namespace useless

namespace stupid
{
    void Foo(){
        std::cout << "stupid foo" << std::endl;
    }
    void Bar(){}
    void DoNothing(unsigned int){}
}//namespace stupid

namespace useless
{
    void DoNothing(int) {}
}//namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo(){
    std::cout << "foo" << std::endl;
}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    // Foo();
    Bar();
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
}//namespace useless
namespace std
{
    void cout()
    {

    }
}

int main()
{


    useless::DoNothing(*useless::g_wasteful);


    for (size_t i = 0; i < 10; i++)
    {
        using useless::Foo;
        
        Foo();
    }
    int i = 10;
    std::cout << i << std::endl;
    {
        int i = 20;
        std::cout << i << std::endl;
    }
    std::cout << i << std::endl;
    
    DoMoreStuff();    

    ::std::cout << 1 ;










    return 0;
}