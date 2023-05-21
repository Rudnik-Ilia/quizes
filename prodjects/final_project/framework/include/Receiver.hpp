#pragma once

#include <fstream>
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
            std::shared_ptr<std::vector<char>> GetDATA();
            
        private:
            int m_sockfd;
            struct sockaddr_in receiverAddr;
            struct sockaddr_in senderAddr;
            // std::unordered_set<uint32_t> receivedPackets;
            std::shared_ptr<std::vector<char>> receivedData;
            std::ofstream m_FILE;

    };

    Receiver::Receiver(): m_FILE("txt.txt", std::ios::binary)
    {
        memset(&receiverAddr, 0, sizeof(struct sockaddr_in ));
        memset(&senderAddr, 0, sizeof(struct sockaddr_in ));
        
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
        m_FILE.close();
    }

    void Receiver::Listen()
    {
        system("clear");

        receivedData = std::make_shared<std::vector<char>>();

        size_t expectID = 1;

        while (1) 
        {
            Datagram datagram;
            socklen_t senderAddrLen = sizeof(senderAddr);
            datagram.m_id = expectID;
            std::cout << "expectID: " <<  datagram.m_id << std::endl;

            ssize_t receivedBytes = recvfrom(m_sockfd, &datagram, MAX_DATAGRAM_SIZE, 0, (struct sockaddr*)&senderAddr, &senderAddrLen);
            if (receivedBytes < 0) 
            {
                std::cerr << "Error receiving data" << std::endl;
            }


            if(datagram.m_id == expectID)
            {
                receivedData->insert(receivedData->end(), datagram.m_data, datagram.m_data + receivedBytes);

                ++expectID;

                if (receivedBytes + HEADER < MAX_DATAGRAM_SIZE) 
                {
                    if(datagram.m_size == receivedData->size())
                    {
                        std::cout << "--------------------------------------------------------Everything is OK!" << std::endl;
                        m_FILE.seekp(datagram.m_from);
                        m_FILE.write(receivedData.get()->data(), receivedData->size());
                        receivedBytes = 0;
                        expectID = 1;
                    }
                    else
                    {
                        std::cout << "====================================ERROR============================================ " << std::endl;
                    }
                    
                    receivedBytes = 0;

                    receivedData->clear();
                    receivedData->shrink_to_fit();

                }
            }
            else
            {
                std::cout << "===================================WRONG ID============================================ " << std::endl;
                expectID = 1;
            }
        }
    }

    int Receiver::GetFD()
    {
        return m_sockfd;
    }

    std::shared_ptr<std::vector<char>> Receiver::GetDATA()
    {
        return receivedData;
    }
}
                // std::cout << "SENDED data size: " <<  datagram.m_size << std::endl;
                // std::cout << "RECEIVED data size: " << totalBytes << std::endl;
                // std::cout << "WRITE it from : " << datagram.m_from << std::endl;
                // std::cout << "DATA : " << receivedData->data() << std::endl;
                // std::cout << "Final data size: " << receivedData->size() << std::endl;
                // std::cout << "id : " << datagram.m_id << std::endl;

                // std::vector<char>(0).swap(*receivedData);
                // receivedData->erase(receivedData->begin(), receivedData->end());