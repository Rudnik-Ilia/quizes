
#include <dlfcn.h>
#include <iostream>

#include "Singleton.hpp"
#include "test_class.hpp"

extern "C"
{
    SimpleTest *GetSingletonPlugin()
    {
        void *dl_handle = nullptr;
        dl_handle  = dlopen("/home/ilia53/git/prodjects/final_project/framework/test/libcreate.so", RTLD_LAZY);

        if (dl_handle == NULL) 
        {
            std::cout << "ERROR1" << std::endl;
            return 0;
        }

        SimpleTest *obj = reinterpret_cast<SimpleTest *>(dlsym(dl_handle, "simpletest"));

        if (obj == NULL) 
        {
            std::cout << "ERROR2" << std::endl;
            return 0;
        }

        dlclose(dl_handle);
        return obj;
    }
}