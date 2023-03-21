#include <iostream>
#include <unistd.h>
using std::cout;

#include "DirMonitor.hpp"

using namespace ilrd;

// gp11 test_dirmonitor.cpp ../src/DirMonitor.cpp -I ../include -lpthread -ldl


int main()
{
    DirMonitor monitor("/home/ilia53/git/prodjects/final_project/framework/test/TEST_FOLDER");
    monitor.Monitor();

    sleep(15);





    return 0;
}