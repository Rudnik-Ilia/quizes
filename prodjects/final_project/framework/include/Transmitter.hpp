#pragma once

#include <mutex>
#include <functional>
#include "Protocol.hpp"
#include "StaticListener.hpp"

namespace ilrd
{
    class Transmitter
    {
        public:
            explicit Transmitter(uint16_t port);
            ~Transmitter();
    
            void SendWrite(std::shared_ptr<std::vector<char>> &dataToSend, u_int64_t m_from,  uint32_t type);
            void SendRead(uint32_t size, u_int64_t from,  uint32_t type, u_int64_t handle);
            int GetFD();
         
        private:
            int m_sockfd;

            struct sockaddr_in receiverAddr;
            
            mutable std::mutex m_mutex{};
            mutable std::mutex m_mutex_2{};
            struct timeval tv;

    };
}