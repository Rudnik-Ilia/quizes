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

#define MAX_DATAGRAM_SIZE 64000
#define HEADER (sizeof(uint32_t) * 3 + sizeof(u_int64_t))

enum status_code
{
    ERROR = 0,
    CORRECT
};

struct Datagram 
{
    uint32_t m_id;
    uint32_t m_num_packed;
    u_int64_t m_from;
    uint32_t m_size;
    char m_data[MAX_DATAGRAM_SIZE - HEADER];

}__attribute__((packed));

struct Acknoledge 
{
    uint32_t m_code;

}__attribute__((packed));
  