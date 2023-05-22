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
            struct timeval tv;
    };



    Transmitter::Transmitter(): m_sockfd(0)
    {
        memset(&receiverAddr, 0, sizeof(struct sockaddr_in ));
        memset(&tv, 0, sizeof(struct timeval));

        m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_sockfd < 0) 
        {
            std::cerr << "Error creating socket" << std::endl;
        }
        receiverAddr.sin_family = AF_INET;
        receiverAddr.sin_port = htons(8080); 
        receiverAddr.sin_addr.s_addr = INADDR_ANY;

        tv.tv_sec = 1;
        tv.tv_usec = 0;

        if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv)) < 0)
        {
            std::cout << "Error setsockopt" << std::endl;
        }
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

            std::cout << "--------------------" << std::endl;
            std::cout << "Size to send: " << m_dataToSend->size() << std::endl;

            socklen_t len = sizeof(receiverAddr);
            size_t totalSentBytes = 0;

            while (totalSentBytes < m_dataToSend->size()) 
            {
                Datagram datagram;
                datagram.m_size = m_dataToSend->size() + HEADER;
                datagram.m_from = from;

                size_t dataLength = std::min((m_dataToSend->size() + HEADER) - totalSentBytes, MAX_DATAGRAM_SIZE - HEADER);

                memcpy(&datagram.m_data, &(*m_dataToSend)[totalSentBytes], dataLength);

                ssize_t sentBytes = sendto(m_sockfd, &datagram, dataLength, 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
                if (sentBytes < 0) 
                {
                    std::cerr << "Error sending data" << std::endl;
                }
                
                totalSentBytes += sentBytes;
                std::cout << "Sended bytes: " <<  totalSentBytes << std::endl;
            }

            Acknoledge ack;

            std::cout << "Wait for acknoledge " << std::endl;

            ssize_t receivedBytes = recvfrom(m_sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&receiverAddr, &len);
            if (receivedBytes < 0) 
            {
                std::cout << "Error receiving data: timeout" << std::endl;
            }

            if(ack.m_code == CORRECT)
            {
                std::cout << "I've got the answer, and check it!" << std::endl;
            }

            // sleep(2);
        } 
    }
}