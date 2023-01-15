/*****************************************************
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

String::String(const char *str): m_str(strdup(str)) 
{}

String::String(const String& str2): m_str(strdup(str2.Cstr())) 
{}

String::~String()
{
    free(m_str);
    m_str = NULL;
}

String& String::operator=(const String& other) 
{
    free(m_str);
    m_str = strdup(other.m_str);
    return *this;
}
size_t String::Length() const
{
    return strlen(m_str);
}
const char *String::Cstr() const 
{
    return m_str;
}