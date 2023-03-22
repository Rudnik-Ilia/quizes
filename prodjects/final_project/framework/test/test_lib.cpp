#include <sys/inotify.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h> // dlopen
#include <iostream>




int main()
{   
    std::cout << "DLLOADER CALL1" << std::endl;
    void *dl_handler = dlopen("/home/ilia53/git/prodjects/final_project/framework/test/lib.so", RTLD_LAZY);
    std::cout << "DLLOADER CALL2" << std::endl;

    if(NULL == dl_handler)
    {
        std::cout << "dlopen mistake" << std::endl;
    }
    std::cout << "DLLOADER CALL3" << std::endl;

    return 0;
}