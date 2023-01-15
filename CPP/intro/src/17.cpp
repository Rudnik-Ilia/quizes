#include <iostream> 
#include <typeinfo> //typeid
using namespace std; 
 

template<typename T> 
void foo(T t) 
{ 
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl; 
} 
 
 
// template<>// for solve problem 
void foo(int n) 
{ 
    std::cout << n << " SIMPLE!!!!!\n"; 
} 
 
/* 
void foo(float t) 
{ 
    std::cout << t << " Specialized foo (for float param)\n"; 
}*/ 
 
int main() 
{ 
    foo(4.2); 
    // foo(2.0f); // output name of data type - float 
    foo(5); 
    foo<int>(5); // int  
 
    return 0; 
}