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
#define HEADER (sizeof(uint32_t) * 3)

struct Datagram 
{
    uint32_t m_id;
    uint32_t m_num_packed;
    uint32_t m_size;
    char m_data[MAX_DATAGRAM_SIZE - HEADER];

}__attribute__((packed));
  