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
    
            inline void Send(std::shared_ptr<std::vector<char>> dataToSend, u_int64_t m_from,  uint32_t type);
            inline void Receiver();
            inline int GetFD();
            inline void SocketHandler();
         
        private:
            int m_sockfd;
            int m_sockfd_spare;
            
            struct sockaddr_in receiverAddr;

            struct sockaddr_in rec_addr;
            struct sockaddr_in sen_addr;
            
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

    void Transmitter::Send(std::shared_ptr<std::vector<char>> m_dataToSend, u_int64_t from,  uint32_t type)
    {
        std::unique_lock<std::mutex> m_lock(m_mutex);
        {
            // system("clear");
label_1:
            std::cout << "--------------------" << std::endl;
            std::cout << "Size to send: " << m_dataToSend->size() << std::endl;

            socklen_t len = sizeof(receiverAddr);
            size_t totalSentBytes = 0;

            while (totalSentBytes < m_dataToSend->size()) 
            {
                Datagram datagram;
                datagram.m_size = m_dataToSend->size() + HEADER;
                datagram.m_from = from;
                datagram.m_type = type;

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
        //     if(ack.m_code == 22)
        //     {
        //         Receiver();
        //     }
        } 
        // std::this_thread::yield();
    }

    void Transmitter::SocketHandler()
    {

    }

    void Transmitter::Receiver()
    {
        struct sockaddr_in rec_addr;
        struct sockaddr_in sen_addr;

        memset(&rec_addr, 0, sizeof(struct sockaddr_in));
        memset(&sen_addr, 0, sizeof(struct sockaddr_in));
        
        m_sockfd_spare = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_sockfd < 0) 
        {
            std::cerr << "Error creating socket" << std::endl;
        }

        int bufferSize = 64000;
        setsockopt(m_sockfd_spare, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

        rec_addr.sin_family = AF_INET;
        rec_addr.sin_port = htons(8888); 
        rec_addr.sin_addr.s_addr = INADDR_ANY;

        // if (bind(m_sockfd_spare, (struct sockaddr*)&rec_addr, sizeof(rec_addr)) < 0) 
        // {
        //     std::cerr << "Error binding second socket" << std::endl;
        // }

        auto receivedData = std::make_shared<std::vector<char>>();

        while (1) 
        {
            Datagram datagram;
            Acknoledge ack;
            socklen_t len = sizeof(sen_addr);
        
            ssize_t receivedBytes = recvfrom(m_sockfd_spare, &datagram, MAX_DATAGRAM_SIZE, 0, (struct sockaddr*)&sen_addr, &len);
            if (receivedBytes < 0) 
            {
                std::cerr << "Error receiving data" << std::endl;
            }

            receivedData->insert(receivedData->end(), datagram.m_data, datagram.m_data + receivedBytes);

            if (receivedBytes + HEADER < MAX_DATAGRAM_SIZE) 
            {
                if(datagram.m_size == receivedData->size())
                {
                    std::cout << "---Everything is OK! on host side---" << std::endl;
                    ack.m_code = CORRECT;
                }
                else
                {
                    std::cout << "WRONG SIZE!" << std::endl;
                    ack.m_code = ERROR;
                }
                std::cout << "Sended data size on host side: " <<  datagram.m_size << std::endl;
                std::cout << "Received data size on host side: " << receivedData->size() << std::endl;

                receivedBytes = 0;
                std::vector<char>(0).swap(*receivedData);
                std::cout << "Final data size on host side: " << receivedData->size() << std::endl;

                // ssize_t sentBytes = sendto(m_sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
                // if (sentBytes < 0) 
                // {
                //     std::cerr << "Error sending data on host side" << std::endl;
                // }

                // std::cout << "Sended ack on host side: " << ack.m_code << std::endl;
            }
        }

    }

    int Transmitter::GetFD()
    {
        return m_sockfd;
    }
}