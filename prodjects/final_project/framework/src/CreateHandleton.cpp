
#define CREATOR
#include "Handleton.hpp"

#include "Logger.hpp"

extern "C"
{
    ilrd::Logger* GetInstance()
    {
        return ilrd::Handleton<ilrd::Logger>::GetInstance();
    }

}