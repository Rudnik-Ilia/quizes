// #define CREATOR
#include <iostream>
using std::cout;
using std::endl;
using std::string;
#include <thread>
using std::thread;
#include <unistd.h>
#include <dlfcn.h>
#include "Factory.hpp"
#include "Singleton.hpp"
#include "ITask.hpp"

using namespace ilrd;
typedef Factory<ITask, string> factory_p;
typedef factory_p(*loadedFunc)();

//  g++ -fPIC -c lib_for_handleton.cpp -I ../include
//  g++ -shared -o libsingle.so lib_for_handleton.o
//  gp11 test_linking.cpp -ldl -I ../include

int main()
{
    SimpleTest *ptr1 = Singleton<SimpleTest>::GetInstance();
    SimpleTest *ptr2 = Singleton<SimpleTest>::GetInstance();

    void *dl_handle2 = nullptr;
    dl_handle2  = dlopen("/home/ilia53/git/prodjects/final_project/framework/test/libcreate.so", RTLD_LAZY);
    if (dl_handle2 == NULL) 
    {
        std::cout << "ERROR3" << std::endl;
        return 0;
    }

    SimpleTest* obj = reinterpret_cast<SimpleTest *>(dlsym(dl_handle2, "simpletest"));

    if (obj == NULL) 
    {
        std::cout << "ERROR4" << std::endl;
        return 0;
    }

    SimpleTest *(*func)(void) = nullptr;
    void *dl_handle = nullptr;
    dl_handle  = dlopen("/home/ilia53/git/prodjects/final_project/framework/test/libplugin.so", RTLD_LAZY);
    if (dl_handle == NULL) 
    {
        std::cout << "ERROR1" << std::endl;
        return 0;
    }

    *(void**)&func = reinterpret_cast<void**>(dlsym(dl_handle, "GetSingletonPlugin"));

    if (func == NULL) 
    {
        std::cout << "ERROR2" << std::endl;
        return 0;
    }


    SimpleTest *ptr3 = (*func)();
    SimpleTest *ptr4 = (*func)();

    std::cout << ptr1 << std::endl;
    std::cout << ptr2 << std::endl;
    std::cout << Singleton<SimpleTest>::GetInstance() << std::endl;
    std::cout << ptr3 << std::endl;
    std::cout << ptr4 << std::endl;
    std::cout << obj << std::endl;
    
    ptr1->My_method();
    ptr2->My_method();
    ptr3->My_method();
    ptr4->My_method();
    obj->My_method();

    dlclose(dl_handle);
    dlclose(dl_handle2);

    return 0;
}
