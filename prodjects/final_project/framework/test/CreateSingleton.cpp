#define CREATOR

#include <iostream>
#include <dlfcn.h>

#include "Handleton.hpp"
#include "Factory.hpp"
#include "ITask.hpp"
#include "test_class.hpp"

#include "Logger.hpp"

using namespace ilrd;

extern "C"
{
    Logger *logger = ilrd::Handleton<Logger>::GetInstance();
}