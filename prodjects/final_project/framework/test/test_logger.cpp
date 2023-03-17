#include <iostream>
#include <unistd.h>
#include <dlfcn.h>

#include "Logger.hpp"
#include "Singleton.hpp"
#include "Handleton.hpp"
#include "LogInherited.hpp"

using namespace ilrd;
typedef Logger*(*func)();
// gp11 test_logger.cpp ../src/LogInherited.cpp ../src/LogMessage.cpp  ../src/LogTask.cpp ../src/Logger.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp  -I ../include -lpthread
int main()
{   

    // Singleton<Logger>::GetInstance()->Log(TraceLog("trace")).Log(DebugLog("debug")).Log(InfoLog("Info")).Log(WarnLog("warn")).Log(ErrorLog("error")).Log(FatalLog("fatal"));
    
    void *dl_handle = nullptr;

    dl_handle  = dlopen("./lib_logger.so", RTLD_LAZY);
    if (dl_handle == NULL) 
    {
        std::cout << "ERROR1" << std::endl;
        return 0;
    }

    func logger_getter = reinterpret_cast<func> (dlsym(dl_handle, "GetLoggerInstance"));
    if (logger_getter == NULL) 
    {
        std::cout << "ERROR2" << std::endl;
        return 0;
    }

    Logger *logger = logger_getter();


    std::cout << "Before" << std::endl;

    logger->SetLevel(ALL);
    logger->Log(DebugLog("someinfo"));

    std::cout << "After" << std::endl;

    sleep(1);

    return 0;
}