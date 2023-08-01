#include <iostream>


bool isTriangular(int A, int B, int C) {

    bool condition1 = (A + B) > C;
    bool condition2 = (A + C) > B;
    bool condition3 = (B + C) > A;

    return condition1 && condition2 && condition3;
}



int main()
{
    std::cout << isTriangular(3,4,5) << std::endl;
    return 0;
}