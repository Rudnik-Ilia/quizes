
#include <cstring>
#include "RCString.hpp"

namespace ilrd
{

RCString::RCS* RCString::Init(const char *str_)
{
    std::size_t size = std::strlen(str_) + 1;
    RCS *ptr = (RCS*)operator new(offsetof(RCS, m_str) + size);
    ptr->m_count = 1;
    memcpy(ptr->m_str, str_, size);
    
    return ptr;
}



}