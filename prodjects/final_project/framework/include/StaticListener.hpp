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
        Acknoledge ack;
        socklen_t len = sizeof(sen_addr);
    
        ssize_t receivedBytes = recvfrom(m_socket, &ack, sizeof(ack), 0, (struct sockaddr*)&sen_addr, &len);
        if (receivedBytes < 0) 
        {
            std::cerr << "Error receiving data" << std::endl;
        }
        if(ack.m_code == 22)
        {
            std::cout << "***************" << std::endl;
        }
    }

    int StaticListener::GetFD()
    {
        return m_socket;
    }
}

