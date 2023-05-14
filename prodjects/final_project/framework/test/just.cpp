#include <vector>
#include <iostream>
#include <memory>

using namespace std;


int main()
{
    auto chunk = std::make_shared<std::vector<int>>(5);
    chunk.get()->push_back(10);
    chunk.get()->push_back(20);
    chunk.get()->push_back(30);

    std::cout <<  << std::endl;
    
    return 0;
}