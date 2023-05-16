#pragma once

#include <linux/nbd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <vector>

#define BLOCK (4096)

namespace ilrd
{
    struct Reply
    {
 

        char data[BLOCK];
    }__attribute__((packed));

    struct Request
    {


        char data[BLOCK];
    }__attribute__((packed));

    struct Header
    {
        size_t id;
        size_t size_of_block;
        size_t num_of_block;

        char data[BLOCK];
        
    }__attribute__((packed));
    
}