#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FRAME.hpp"
#include "TasksNBD.hpp"
// g++ test_frame.cpp ../src/NBD.cpp ../src/Reactor.cpp -I ../include
using namespace ilrd;
static void *data;


void Show(void *dat, u_int64_t offset)
{
    for (size_t i = 0; i < 100; i++)
    {
        std::cout<<  *((char*)data + offset + i);
    }  
}
int my_read(void *buf, u_int32_t len, u_int64_t offset)
{   
    std::cout << "My_read" << std::endl;
    memcpy(buf, (char *)data + offset, len);
    return 0;
}

int my_write(const void *buf, u_int32_t len, u_int64_t offset)
{
    std::cout << "My_write" << std::endl;
    memcpy((char *)data + offset, buf, len);
    return 0;
}


int main(int argc, char *argv[])
{
    // std::string str1 = "ilia";
    // ArgsForRead arg_read(str1);
    // ArgsForWrite arg_write(str1, 777);
    
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

    Factory<ITask, Reactor::ioMode> factory;
    NBDServer nbd(&aop, "/dev/nbd0");

    FRAME frame(nbd, factory);
    
    frame.Register(Reactor::ioMode::READ, Creator::Get_Read_Task);
    frame.Register(Reactor::ioMode::WRITE, Creator::Get_Write_Task);

    frame.Run_Reactor();

    return 0;   
}
