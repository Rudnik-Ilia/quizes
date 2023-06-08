#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FRAME.hpp"
#include "Transmitter.hpp"

// #include "TasksNBD.hpp"LD g++ test_frame.cpp ../src/NBD.cpp ../src/FRAME.cpp ../src/Reactor.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp -lpthread -I -lconfig++ ../include
// g++ test_frame.cpp ../src/NBD.cpp ../src/Reactor.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp -lpthread -I ../include

using namespace ilrd;

int main(int argc, char *argv[])
{  
    struct buse_operations aop = {
        .size = 128 * (1024*1024),
    };

    NBDServer nbd(&aop, "/dev/nbd0");
    FRAME frame(nbd);
    
    frame.Run_Reactor();

    return 0;   
}
