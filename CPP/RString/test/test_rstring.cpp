#include <iostream>
#include <cstdlib>
#include "RCString.hpp"


using namespace ilrd;



int main()
{

    RCString str("hello");

    RCString str1(str);
    RCString str2(str1);

    RCString str3("hi");
    RCString str4(str3);

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

    std::cout << (str1 == str2) << std::endl;
    std::cout << (str1 != str3) << std::endl;

    RCString str0;
    RCString str00;
    RCString str000;

    str0.ShowAddr();
    str00.ShowAddr();
    str000.ShowAddr();

    str000.ShowCount();

    std::cout << str[1] << std::endl;
    std::cout << str3[1] << std::endl;

    char o = str1[4];

    std::cout << o << std::endl;

    str3[0] = 'a';
    std::cout << str3 << std::endl;

    str1[0] = 'k';
    
    std::cout << str1 << std::endl;

    // RCString str5("ilia");
    // str5[0] = str5[3];
    // std::cout << str5 << std::endl;

    str.ShowCount();
    str1.ShowCount();


    return 0;
}