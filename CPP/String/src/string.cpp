/****************************************************
* Topic: String                                               
* Author: Rudnik Ilia                                
* Date: 15.01.2023                                
* Reviewer: Tim                         
* Review status: reviewed                            
*****************************************************/

#include <cstdlib>
#include <cstring> 
#include "string.hpp"

using namespace ilrd;

String::String(const char *str): m_str(new char[strlen(str) + 1]) 
{
    memcpy(m_str, str, strlen(str) + 1);  
}

String::String(const String&  other): m_str(new char[other.Length()+1])
{
     memcpy(m_str, other.m_str, other.Length() + 1);
}

String::~String()
{
    delete[] m_str;
    m_str = NULL;
}

size_t String::Length() const
{
    return strlen(m_str);
}

const char* String::Cstr() const 
{
    return this->m_str;
}

String &String::operator=(const String &other)
{
    delete[] m_str;
    m_str = new char[strlen(other.m_str) + 1];
    memcpy(m_str, other.m_str, strlen(other.m_str) + 1);
    return *this;
}
// SECOND VRIANT---------------------------------------------------------------------------------

// String::String(const char *str): m_str(strdup(str)) 
// {
//     if(m_str == NULL)
//     {
//         return;
//     }
// }

// String::String(const String& str2): m_str(strdup(str2.Cstr())) 
// {
//      if(m_str == NULL)
//     {
//         return;
//     }
// }

// String::~String()
// {
//     free(m_str);
//     m_str = NULL;
// }

// String& String::operator=(const String& other) 
// {
//     free(m_str);
//     m_str = strdup(other.m_str);
//     return *this;
// }
// size_t String::Length() const
// {
//     return strlen(m_str);
// }
// const char *String::Cstr() const 
// {
//     return m_str;
// }