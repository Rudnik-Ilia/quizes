#include <future>
#include <iostream>
#include <thread>




int main(int argc, char *argv[])
{
    int count = 10;

    auto fut_1 = std::async(std::launch::async, [&count]{
            for(int i=0; i<count; ++i) 
            {
                std::cout << 1;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            } 
        });



    auto fut_2 = std::async(std::launch::async, [&count]{
            for(int i=0; i<count; ++i)
            {
                std::cout << 2;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            } 
        });

    fut_1.get();

    return 0;
}