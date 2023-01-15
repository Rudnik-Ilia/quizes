#include <iostream>
#include "head_16.hpp"

void Foo(){
    std::cout << Max<int>(3, 5) << " " << Max<double>(3.7, 12.9) << " ";
}