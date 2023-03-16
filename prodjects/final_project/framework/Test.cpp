#include <dlfcn.h>
#include <unistd.h>

#include "Logger.hpp"
#include "LogInherited.hpp"

using namespace ilrd;
using namespace std;

int main()
{

    void *handleton_lib = dlopen("/home/johnatan/git/projects/final_project/framework/lib_logger.so", RTLD_LAZY);

    if (handleton_lib == 0)
    {
        cout << "something went wrong 2 " << endl;
        return 1;
    }


    Logger *logger = reinterpret_cast<Logger *(*)()>(dlsym(handleton_lib, "logger_instance"))();



    DebugLog ld("TestDebug");
    InfoLog li("TestInfo");
    WarnLog lw("TestWarn");
    ErrorLog le("TestError");
    FatalLog lf("TestFatal");
  

    logger->SetLevel(ALL);


    logger->Log(ld);
    logger->Log(li);
    logger->Log(lw);
    logger->Log(le);
    logger->Log(lf);


    sleep(1);

    return 0;
}
