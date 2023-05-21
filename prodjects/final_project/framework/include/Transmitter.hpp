#pragma once

#include <mutex>

#include "Protocol.hpp"

namespace ilrd
{
    class Transmitter
    {
        public:
            inline explicit Transmitter();
            inline ~Transmitter();
    
            inline void Send(std::shared_ptr<std::vector<char>> dataToSend, u_int64_t m_from);
         
        private:
            int m_sockfd;
            // std::shared_ptr<std::vector<char>> m_dataToSend;
            struct sockaddr_in receiverAddr;
            mutable std::mutex m_mutex{};
    };



    Transmitter::Transmitter(): m_sockfd(0)
    {
        memset(&receiverAddr, 0, sizeof(struct sockaddr_in ));

        m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_sockfd < 0) 
        {
            std::cerr << "Error creating socket" << std::endl;
        }
        receiverAddr.sin_family = AF_INET;
        receiverAddr.sin_port = htons(8080); 
        receiverAddr.sin_addr.s_addr = INADDR_ANY;
    }

    Transmitter::~Transmitter()
    {
        close(m_sockfd);
    }

    void Transmitter::Send(std::shared_ptr<std::vector<char>> m_dataToSend, u_int64_t from)
    {
        std::unique_lock<std::mutex> m_lock(m_mutex);
        {
            // system("clear");
            // std::cout << m_dataToSend->size() << std::endl;
            size_t totalSentBytes = 0;
            uint32_t assign_id = 1;

            while (totalSentBytes < m_dataToSend->size()) 
            {
                Datagram datagram;
                datagram.m_size = m_dataToSend->size() + HEADER;
                datagram.m_from = from;
                datagram.m_id = assign_id;
                std::cout << "assign_id: " <<  assign_id << std::endl;

                size_t dataLength = std::min((m_dataToSend->size() + HEADER) - totalSentBytes, MAX_DATAGRAM_SIZE - HEADER);

                memcpy(&datagram.m_data, &(*m_dataToSend)[totalSentBytes], dataLength);

                ssize_t sentBytes = sendto(m_sockfd, &datagram, dataLength, 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));

                if (sentBytes < 0) 
                {
                    std::cerr << "Error sending data" << std::endl;
                }
                totalSentBytes += sentBytes;
                ++assign_id;
            }
            // sleep(1);
        }
        
    }
}