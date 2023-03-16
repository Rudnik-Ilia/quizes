#include <iostream>
#include <unistd.h>
#include "Logger.hpp"
#include "Singleton.hpp"
#include "LogInherited.hpp"

using namespace ilrd;

int main()
{   
    Singleton<Logger>::GetInstance()->Log(TraceLog("trace")).Log(DebugLog("debug")).Log(InfoLog("Info")).Log(WarnLog("warn")).Log(ErrorLog("error")).Log(FatalLog("fatal"));
    
    sleep(1);

    return 0;
}