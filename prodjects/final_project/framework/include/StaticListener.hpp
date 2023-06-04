#pragma once

#include "Protocol.hpp"

namespace ilrd
{
    class StaticListener
    {
        public:
            inline StaticListener();
            inline ~StaticListener();
            inline void Receiver();
            inline int GetFD();

        private:
            int m_socket;

            struct sockaddr_in rec_addr;
            struct sockaddr_in sen_addr;
    };
        

    StaticListener::StaticListener()
    {
        memset(&rec_addr, 0, sizeof(struct sockaddr_in));
        memset(&sen_addr, 0, sizeof(struct sockaddr_in));
        
        m_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_socket < 0) 
        {
            std::cerr << "Error creating socket" << std::endl;
        }

        int bufferSize = 64000;
        setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

        rec_addr.sin_family = AF_INET;
        rec_addr.sin_port = htons(8082); 
        rec_addr.sin_addr.s_addr = INADDR_ANY;
        
        struct timeval read_timeout;
        read_timeout.tv_sec = 0;
        read_timeout.tv_usec = 10;

        setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);

        if (bind(m_socket, (struct sockaddr*)&rec_addr, sizeof(rec_addr)) < 0) 
        {
            std::cerr << "Error binding socket" << std::endl;
        }
    }

    StaticListener::~StaticListener()
    {
        close(m_socket);
    }
           
    void StaticListener::Receiver()
    {
        auto receivedData = std::vector<char>(0);
        // while(1)
        // {
            Datagram datagram;
            memset(&datagram, 0, sizeof(datagram));

            socklen_t len = sizeof(sen_addr);

            ssize_t receivedBytes = recvfrom(m_socket, &datagram, MAX_DATAGRAM_SIZE, 0, (struct sockaddr*)&sen_addr, &len);
            if (receivedBytes < 0) 
            {
                std::cerr << "Error receiving data from static" << std::endl;
                return;
            }

            receivedData.insert(receivedData.end(), datagram.m_data, datagram.m_data + (receivedBytes - HEADER));

            if (receivedBytes < MAX_DATAGRAM_SIZE) 
            {
                if(datagram.m_size == receivedData.size())
                {
                    std::cout << "---Everything is OK! from static---" << std::endl;
                    // break;
                }
                else
                {
                    std::cout << "WRONG SIZE!  from static" << std::endl;
                    // break;
                }
                std::cout << "Sended data size  from static: " <<  datagram.m_size << std::endl;
                std::cout << "Received data size from static: " << receivedData.size() << std::endl;


                receivedBytes = 0;
                std::vector<char>(0).swap(receivedData);
                std::cout << "Final data size from static: " << receivedData.size() << std::endl;
            }
           

        // }
        
    }

    int StaticListener::GetFD()
    {
        return m_socket;
    }
}   
