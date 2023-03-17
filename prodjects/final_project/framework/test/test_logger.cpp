#include <iostream>
#include <unistd.h>
#include <dlfcn.h>

#include "Logger.hpp"
#include "Singleton.hpp"
#include "LogInherited.hpp"

// g++ -shared -fPIC -o lib_logger.so ../src/*.cpp -I ../include
using namespace ilrd;
// gp11 test_logger.cpp ../src/LogInherited.cpp ../src/LogMessage.cpp  ../src/LogTask.cpp ../src/Logger.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp  -I ../include -lpthread
int main()
{   
    Singleton<Logger>::GetInstance()->Log(TraceLog("trace")).Log(DebugLog("debug")).Log(InfoLog("Info")).Log(WarnLog("warn")).Log(ErrorLog("error")).Log(FatalLog("fatal"));
    
    // void *dl_handle = nullptr;

    // dl_handle  = dlopen("/home/ilia53/git/prodjects/final_project/framework/test/lib_logger.so", RTLD_LAZY);
    // if (dl_handle == NULL) 
    // {
    //     std::cout << "ERROR1" << std::endl;
    //     return 0;
    // }

    // Logger *logger = reinterpret_cast<Logger *>(dlsym(dl_handle, "logger"));

    // if (logger == NULL) 
    // {
    //     std::cout << "ERROR2" << std::endl;
    //     return 0;
    // }

    // std::cout << "!!!" << std::endl;

    // logger->SetLevel(ALL);

    // logger->Log(DebugLog("someinfo"));

    // std::cout << "???" << std::endl;

    sleep(1);

    return 0;
}