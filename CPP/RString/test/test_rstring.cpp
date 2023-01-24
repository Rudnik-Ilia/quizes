#include <iostream>
#include <cstdlib>
#include "RCString.hpp"


using namespace ilrd;



int main()
{

    RCString str("hello");

    RCString *str6 = new RCString(str);
   
    RCString str1(str);
    RCString str2(str1);

    RCString str3("hi");
    RCString str4(str3);



    // RCString str5;
    str.ShowAddr();
    str1.ShowAddr();
    str2.ShowAddr();

    str3.ShowAddr();
    str4.ShowAddr();

    str6->ShowAddr();

    str1.ShowCount();
    str2.ShowCount();

    std::cout << (str1 == str2) << std::endl;
    std::cout << (str1 != str3) << std::endl;

    RCString str0;
    RCString str00;
    RCString str000;

    str0.ShowAddr();
    str00.ShowAddr();
    str000.ShowAddr();

    std::cout << str[0] << std::endl;

    // str1[0] = 'z';

    char s = str1[3];

    std::cout << s << std::endl;

    str1[1] = 'k';
    std::cout << str << std::endl;
    
    // throw 1;

    // free(*(void**)&str);

    

    


   
    

    



    return 0;
}