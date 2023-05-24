#pragma once

#include <assert.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

#include "TasksNBD.hpp"

#ifndef BUSE_DEBUG
#define BUSE_DEBUG (0)
#endif

#define htonll ntohll

namespace ilrd
{
    #ifdef WORDS_BIGENDIAN
    u_int64_t ntohll(u_int64_t a) 
    { 
        return a; 
    }
    #else
    inline u_int64_t ntohll(u_int64_t a)
    {
        u_int32_t lo = a & 0xffffffff;
        u_int32_t hi = a >> 32U;
        lo = ntohl(lo);
        hi = ntohl(hi);
        return ((u_int64_t)lo) << 32U | hi;
    }
    #endif
    struct buse_operations 
    {
        int (*read)(void *buf, u_int32_t len, u_int64_t offset);
        int (*write)(const void *buf, u_int32_t len, u_int64_t offset);
        void (*disc)();
        int (*flush)();
        int (*trim)(u_int64_t from, u_int32_t len);

        u_int64_t size;
        u_int32_t blksize;
        u_int64_t size_blocks;
    };

    class IDriver
    {
        public:
            IDriver() = default;
    };
    class NBDServer : public IDriver
    {
        public:
            NBDServer(struct buse_operations* aop, const char* dev_file);
            ~NBDServer();
         
            static void disconnect_nbd(int signal); 
            int write_all(int fd, char* buf, size_t count);
            int read_all(int fd, char* buf, size_t count);
            int set_sigaction(int sig, const struct sigaction * act); 
     
            int Serve(); 
            int Init();
            int HandlerStaff();
            int Buse_main();
            int Quit();
            void Start();

            int GetDescriptor();
            std::shared_ptr<struct ArgumentsForTask>& GetArguments();
        
        private:
            static int nbd_dev_to_disconnect;
            const struct buse_operations* aop_;
            const char* dev_file;
            int sp[2];
            int nbd;
            int err;
            int flags;
            pid_t pid; 
            std::shared_ptr<struct ArgumentsForTask> m_args;
    };
}