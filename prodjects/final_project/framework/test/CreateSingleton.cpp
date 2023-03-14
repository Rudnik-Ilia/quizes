#define CREATOR

#include <iostream>
#include <dlfcn.h>

#include "Singleton.hpp"
#include "Factory.hpp"
#include "ITask.hpp"
#include "test_class.hpp"

using namespace ilrd;

extern "C"
{
    SimpleTest *simpletest = ilrd::Singleton<SimpleTest>::GetInstance(); 
}