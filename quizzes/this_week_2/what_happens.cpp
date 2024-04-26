#include <iostream>
#include <unistd.h>
#include <thread>


using namespace std;

static int  i = 1;

void printI()
{
    ++i;
    printf("%d\n",  i);
}
void threadProc()
{
    // sleep(5);
    printI();
}

int main() 
{
    std::thread t1 = std::thread(&threadProc);
    std::thread t2 = std::thread(&threadProc);

    t1.join();
    t2.join();

}


