#pragma once

#include "Protocol.hpp"

namespace ilrd
{
    class Receiver
    {
        public:
            Receiver();
            ~Receiver();
            void Listen();
            int GetFD();
            
        private:
            int m_sockfd;
            struct sockaddr_in receiverAddr;
            struct sockaddr_in senderAddr;
            // std::unordered_set<uint32_t> receivedPackets;
            std::shared_ptr<std::vector<char>> receivedData;

    };

    Receiver::Receiver()
    {
        m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_sockfd < 0) 
        {
            std::cerr << "Error creating socket" << std::endl;
        }

        int bufferSize = 64000;

        setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

        receiverAddr.sin_family = AF_INET;
        receiverAddr.sin_port = htons(8080); 
        receiverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(m_sockfd, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr)) < 0) 
        {
            std::cerr << "Error binding socket" << std::endl;
        }
    }
    Receiver::~Receiver()
    {
        close(m_sockfd);
    }

    void Receiver::Listen()
    {
        system("clear");
        auto receivedData = std::make_shared<std::vector<char>>();

        while (1) 
        {
            Datagram acknoledge;
            socklen_t senderAddrLen = sizeof(senderAddr);

            ssize_t receivedBytes = recvfrom(m_sockfd, &acknoledge, MAX_DATAGRAM_SIZE, 0, (struct sockaddr*)&senderAddr, &senderAddrLen);
            if (receivedBytes < 0) 
            {
                std::cerr << "Error receiving data" << std::endl;
            }

            receivedData->insert(receivedData->end(), acknoledge.m_data, acknoledge.m_data + receivedBytes);

            if (receivedBytes + HEADER < MAX_DATAGRAM_SIZE) 
            {
                if(acknoledge.m_size == receivedData->size())
                {
                    std::cout << "Everything is OK!" << std::endl;
                }
                std::cout << "SIZE : " <<  acknoledge.m_size << std::endl;
                std::cout << "Received data size: " << receivedData->size() << std::endl;
                std::cout << "DATA : " << receivedData->data() << std::endl;

                receivedBytes = 0;
                receivedData->clear();

                // std::cout << "Final data size: " << receivedData.size() << std::endl;
                // std::cout << "id : " << acknoledge.m_id << std::endl;
            }
        }
    }

    int Receiver::GetFD()
    {
        return m_sockfd;
    }
}