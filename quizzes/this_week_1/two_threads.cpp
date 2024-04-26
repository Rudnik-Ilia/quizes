#include <iostream>
#include <thread>
#include <unistd.h>


static size_t counter = 0;

static void Work()
{
    for(int i = 0; i < 1000000; ++i)
    {
        // std::lock_guard<std::mutex> lock(counterMutex);
        counter++;
    }
}


int main()
{

    std::thread pool[2];

    for(int i = 0; i < 2; ++i)
    {
        pool[i] = std::thread(&Work);
    }

    for(int i = 0; i < 2; ++i)
    {
        pool[i].join();
    }


    std::cout << counter << std::endl;
}
