#define CREATOR

#include <iostream>
#include <dlfcn.h>

#include "Singleton.hpp"
// #include "Handleton.hpp"
// #include "Factory.hpp"
#include "ITask.hpp"
#include "Logger.hpp"
#include "LogTask.hpp"
#include "LogInherited.hpp"

using namespace ilrd;

extern "C"
{
    Logger *logger = ilrd::Singleton<Logger>::GetInstance();
}