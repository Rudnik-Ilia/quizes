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
            inline explicit Transmitter();
            inline ~Transmitter();
    
            inline void Send(std::vector<char> &dataToSend, u_int64_t m_from,  uint32_t type);
            inline void SendRead(uint32_t size, u_int64_t from,  uint32_t type);
            inline int GetFD();
         
        private:
            int m_sockfd;
            int m_sockfd_spare;

            struct sockaddr_in receiverAddr;
            
            mutable std::mutex m_mutex{};
            struct timeval tv;

    };


    Transmitter::Transmitter(): m_sockfd(0), m_sockfd_spare(0)
    {
        memset(&receiverAddr, 0, sizeof(struct sockaddr_in));
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

    void Transmitter::Send(std::vector<char> &m_dataToSend, u_int64_t from,  uint32_t type)
    {
        std::lock_guard<std::mutex> m_lock(m_mutex);
        {
            // system("clear");
label_1:
            std::cout << "--------------------" << std::endl;
            std::cout << "Size to send: " << m_dataToSend.size() << std::endl;

            socklen_t len = sizeof(receiverAddr);
            size_t totalSentBytes = 0;

            while (totalSentBytes < m_dataToSend.size()) 
            {
                Datagram datagram;
                memset(&datagram, 0, sizeof(datagram));

                datagram.m_size = m_dataToSend.size() + HEADER;
                datagram.m_from = from;
                datagram.m_type = type;

                size_t dataLength = std::min((m_dataToSend.size() + HEADER) - totalSentBytes, MAX_DATAGRAM_SIZE - HEADER);

                std::cout <<"dataLength: " << dataLength << std::endl;
                std::cout <<"totalSentBytes: " << totalSentBytes << std::endl;

                memcpy(&datagram.m_data, &m_dataToSend[totalSentBytes], dataLength);

                ssize_t sentBytes = sendto(m_sockfd, &datagram, dataLength, 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
                if (sentBytes < 0) 
                {
                    std::cerr << "Error sending data" << std::endl;
                }
                
                totalSentBytes += sentBytes;
                std::cout << "Sended bytes: " <<  totalSentBytes << std::endl;
            }

            Acknoledge ack;
            memset(&ack, 0, sizeof(ack));
            std::cout << "Wait for acknoledge " << std::endl;

            ssize_t receivedBytes = recvfrom(m_sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&receiverAddr, &len);
            if (receivedBytes < 0) 
            {
                goto label_1;
                std::cout << "Error receiving data: timeout" << std::endl;
            }

            if(ack.m_code == CORRECT)
            {
                std::cout << "I've got the answer, and check it!" << std::endl;
            }
            if(ack.m_code == ERROR)
            {
                goto label_1;
                std::cout << "We lost something..........Sorry!" << std::endl;
            }
            if(ack.m_code == 22)
            {
                // Receiver();
                std::cout << "22 from transmitter!!!!!!" << std::endl;

            }
        } 
        // std::this_thread::yield();
    }

    void Transmitter::SendRead(uint32_t size, u_int64_t from,  uint32_t type)
    {
        Datagram datagram;

        datagram.m_size = size;
        datagram.m_from = from;
        datagram.m_type = type;

        ssize_t sentBytes = sendto(m_sockfd, &datagram, MAX_DATAGRAM_SIZE, 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
        if (sentBytes < 0) 
        {
            std::cerr << "Error sending data" << std::endl;
        }
        std::cout << "Send read-request task from transmitter" << std::endl;
    }

    int Transmitter::GetFD()
    {
        return m_sockfd;
    }
}