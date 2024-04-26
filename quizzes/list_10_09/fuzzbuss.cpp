#include <iostream>

void FB(int start, int stop)
{
    for(size_t i =  start; i < stop; ++i)
    {
        if(i % 3 == 0 && i % 5 == 0)
        {
            std::cout << 'C';
            std::cout << ' '; 
            continue;
        }
        else if(i % 3 == 0)
        {
            std::cout << 'A';
            std::cout << ' '; 
            continue;
        }
        else if(i % 5 == 0)
        {
            std::cout << 'B';
            std::cout << ' '; 
            continue;
        }
        std::cout << i;
        std::cout << ' '; 
    }
}


int main()
{
    FB(1, 101);
    return 0;
}