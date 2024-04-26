
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FRAME.hpp"
#include "Transmitter.hpp"

//  g++ test_frame.cpp ../src/NBD.cpp ../src/FRAME.cpp ../src/Reactor.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp ../src/StaticListener.cpp ../src/Transmitter.cpp -lpthread -lconfig++ -I ../include


using namespace ilrd;

int main()
{  
    struct buse_operations aop = {
        .size = 128 * (1024*1024),
    };

    NBDServer nbd(&aop, "/dev/nbd0");
    FRAME frame(nbd);
    
    frame.Run_Reactor();

    return 0;   
}
