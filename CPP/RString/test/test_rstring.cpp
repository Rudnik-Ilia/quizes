#include <iostream>
#include <cstdlib>
#include "RCString.hpp"
#include "test.h"


using namespace ilrd;



int main()
{
    RCString str("hello");

    RCString str1(str);
    RCString str2(str1);

    RCString str3("hi");
    RCString str4(str3);

    TEST("test",(str1 == str2), 1);
    TEST("test",(str1 != str3), 1);

 #ifndef NDEBUG
    str.ShowAddr();
    str1.ShowAddr();
    str2.ShowAddr();

    str3.ShowAddr();
    str4.ShowAddr();

    str.ShowCount();
    str1.ShowCount();
    str2.ShowCount();

    str3.ShowCount();
    str4.ShowCount();
#endif 
    RCString str0;
    RCString str00;
    RCString str000;
#ifndef NDEBUG
    str0.ShowAddr();
    str00.ShowAddr();
    str000.ShowAddr();

    str000.ShowCount();

    str0.ShowAddr();
    str00.ShowAddr();
    str000.ShowAddr();
#endif 

    TEST("test", str1[1] == 'e', 1);
    TEST("test", str3[1] == 'i', 1);
    TEST("test", str1[0] == str3[0], 1);
    TEST("test", str1[4] == 'o', 1);

    str3[0] = 'a';
    TEST("test", str3[0] == 'a', 1);

    str1[0] = 'k';
    TEST("test", str1[0] == 'k', 1);

    // RCString str5("ilia");
    // str5[0] = str5[3];
    // std::cout << str5 << std::endl;
#ifndef NDEBUG
    str.ShowCount();
    str1.ShowCount();
#endif 

    return 0;
}