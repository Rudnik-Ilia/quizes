#pragma once

#include <fstream>
#include "Protocol.hpp"

namespace ilrd
{
    class Receiver
    {
        public:
            explicit Receiver(uint16_t port);
            ~Receiver();

            void Listen();
            int GetFD();
            void GetReadRequest(u_int64_t from, uint32_t size);

            void Send(std::shared_ptr<std::vector<char>> dataToSend, u_int64_t m_from, u_int64_t handle, uint32_t type);
            
        private:
            int m_sockfd;
            struct sockaddr_in receiverAddr;
            struct sockaddr_in senderAddr;
            std::fstream m_FILE;
            std::shared_ptr<std::vector<char>> m_data;
    };

}
