#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>

#define MAX_DATAGRAM_SIZE (size_t)64000
#define HEADER (sizeof(uint32_t) * 3)

struct Datagram 
{
    uint32_t m_id;
    uint32_t m_num_packed;
    uint32_t m_size;
    char m_data[MAX_DATAGRAM_SIZE - HEADER];

}__attribute__((packed));

namespace ilrd
{
    class Transmitter
    {
        public:
            explicit Transmitter(std::shared_ptr<std::vector<char>> dataToSend);
            ~Transmitter();
    
            void Send();
         
        private:
            int m_sockfd;
            std::shared_ptr<std::vector<char>> m_dataToSend;
            struct sockaddr_in receiverAddr;
    };

    Transmitter::Transmitter(std::shared_ptr<std::vector<char>> dataToSend): m_sockfd(0), m_dataToSend(dataToSend)
    {
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

    void Transmitter::Send()
    {

        size_t totalSentBytes = 0;
        uint32_t assign_id = 1;

        while (totalSentBytes < m_dataToSend->size()) 
        {
            Datagram datagram;
            datagram.m_size = m_dataToSend->size();
            // datagram.m_id = assign_id;

            size_t dataLength = std::min(m_dataToSend->size() - totalSentBytes, MAX_DATAGRAM_SIZE - HEADER);

            memcpy(&datagram.m_data, &(*m_dataToSend)[totalSentBytes], dataLength);

            ssize_t sentBytes = sendto(m_sockfd, &datagram, dataLength, 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
            if (sentBytes < 0) 
            {
                std::cerr << "Error sending data" << std::endl;
            }
            totalSentBytes += sentBytes;
            // ++assign_id;
        }


}
}