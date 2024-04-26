#include <iostream>

int main()
{
    int x = 5; // Outer variable x

    std::cout << "Outer x: " << x << std::endl;

    {
        int x = 10; // Inner variable x, shadows the outer x
        std::cout << "Inner x: " << x << std::endl;
    }

    std::cout << "Outer x after inner scope: " << x << std::endl;

    return 0;
}