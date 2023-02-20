#include <iostream>
#include <cstring> 
#include <ostream>
#include "test.h"
#include "string.hpp"

using namespace ilrd;



int main()
{
    

    String s1("Rudnik");
    String s2(s1);
    String s3("Ilia");

    TEST("len",  strlen("Rudnik"), s1.Length());
    TEST("len",  strlen("Rudnik"), s2.Length());
    TEST("len",  strcmp(s1.Cstr(), s2.Cstr()), 0);
    TEST("len",  (s1 == s2), 1);
    TEST("len",  (s1 > s3), 1);
    TEST("len",  (s1 < s3), 0);

    std::cout << s1[0] << std::endl;
    std::cout << s1 << std::endl;

    

  

    PASS;
    return 0;
}