#pragma once
#include <linux/nbd.h>
#include <cassert>
#include <fcntl.h>
#include "Protocol.hpp"


namespace ilrd
{
    class StaticListener
    {
        public:
            StaticListener();
            ~StaticListener();
            void Receiver(int FD);
            int GetFD();

            int WriteOnFD(int fd, char* buf, size_t count);

        private:
            int m_socket;

            struct sockaddr_in rec_addr;
            struct sockaddr_in sen_addr;
    };
}   
