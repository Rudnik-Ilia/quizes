#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int min_value = 1;
    int max_value = 100;

 
    std::uniform_int_distribution<int> distribution(min_value, max_value);

    int random_number = distribution(gen);

    std::cout << "Random Number: " << random_number % 22 << std::endl;

    return 0;
}
