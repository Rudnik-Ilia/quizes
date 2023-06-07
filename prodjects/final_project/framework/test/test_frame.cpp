#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FRAME.hpp"
#include "Transmitter.hpp"

// #include "TasksNBD.hpp"LD g++ test_frame.cpp ../src/NBD.cpp ../src/FRAME.cpp ../src/Reactor.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp -lpthread -I ../include
// g++ test_frame.cpp ../src/NBD.cpp ../src/Reactor.cpp ../src/ThreadPool.cpp ../src/WorkerThread.cpp ../src/ThreadMap.cpp -lpthread -I ../include

using namespace ilrd;
static void *data;

int my_read(void *buf, u_int32_t len, u_int64_t offset)
{   
    memcpy(buf, (char *)data + offset, len);
    return 0;
}

int my_write(const void *buf, u_int32_t len, u_int64_t offset)
{
    memcpy((char *)data + offset, buf, len);
    return 0;
}

int main(int argc, char *argv[])
{  
    struct buse_operations aop = {
        .read = my_read,
        .write = my_write,
        .size = 128 * (1024*1024),
    };

    data = malloc(aop.size);
    if (data == NULL) 
    {
        err(EXIT_FAILURE, "failed to alloc space for data");
    }


    NBDServer nbd(&aop, "/dev/nbd0");
    FRAME frame(nbd);
    
    frame.Run_Reactor();

    free(data);

    return 0;   
}
