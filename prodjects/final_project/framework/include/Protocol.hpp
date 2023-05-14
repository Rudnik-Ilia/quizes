#pragma once

#include <linux/nbd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <vector>

// namespace ilrd
// {
//     struct Protocol_Reply
//     {
//         u_int32_t type;
//         std::shared_ptr<std::vector<char>> &data;

//     }__attribute__((packed));
// }