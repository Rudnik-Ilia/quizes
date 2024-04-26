#pragma once

#include <linux/nbd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <unordered_set>
#include <memory>

#define MAX_DATAGRAM_SIZE (size_t)64000
#define HEADER (sizeof(uint32_t) * 3 + sizeof(u_int64_t) * 2)
#define NBD_REPLY_MAGIC 0x67446698
#define RED " \033[1;31m "
#define OFFCOLOR " \033[0m\n "

enum status_code
{
    ERROR = 0,
    CORRECT, 
    READ,
    WRITE
};

struct Datagram 
{
    u_int64_t m_handle;	
    uint32_t m_id;
    uint32_t m_type;
    u_int64_t m_from;
    uint32_t m_size;
    char m_data[MAX_DATAGRAM_SIZE - HEADER];

}__attribute__((packed));

struct Acknoledge 
{
    uint32_t m_code;

}__attribute__((packed));
  