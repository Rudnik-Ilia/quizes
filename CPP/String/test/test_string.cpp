#include <iostream>
#include <cstring> 
#include "test.h"
#include "string.hpp"

using namespace ilrd;



int main()
{
    
    
    char *str = "Rudnik";
    String s1(str);
    String s2(s1);

    TEST("len",  strlen(str), s1.Length());
    TEST("len",  strlen(str), s2.Length());
    TEST("len",  strcmp(s1.Cstr(), s2.Cstr()), 0);
 




    PASS;
    return 0;
}