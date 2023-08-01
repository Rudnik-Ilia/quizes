#include <iostream>
#include "task.hpp"

int main()
{
    Summarray<5> summ;

    summ.Insert(4);
    summ.Insert(5);
    summ.Insert(3);
    summ.Insert(2);
    summ.Insert(1);
    summ.Insert(1);
    // summ.Insert(55);
    // summ.Insert(77);
    
    // summ.Insert(10);
    // summ.Insert(5);
    // summ.Insert(9);
    // summ.Insert(9);
    // summ.Insert(9);
    
    std::cout << summ.IsEmpy() << std::endl;
    summ.Delete(5);

    std::cout << summ.IsFull() << std::endl;
    std::cout << summ.Summ() << std::endl;
    std::cout << summ.First() << std::endl;
    // std::cout << summ.Previous(5) << std::endl;
    // std::cout << summ.First() << std::endl;


    return (0);
}