#pragma once
#include <linux/nbd.h>
#include <cassert>
#include "Protocol.hpp"


namespace ilrd
{
    class StaticListener
    {
        public:
            inline StaticListener();
            inline ~StaticListener();
            inline void Receiver(int FD);
            inline int GetFD();

            inline int WriteOnFD(int fd, char* buf, size_t count);

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
        read_timeout.tv_usec = 1;
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
           
    void StaticListener::Receiver(int FD)
    {

        int stop = 1;
        auto receivedData = std::vector<char>(0);

        while(stop) 
        {
            Datagram datagram;
            memset(&datagram, 0, sizeof(datagram));

            struct nbd_reply reply;
            
            socklen_t len = sizeof(sen_addr);
        
            ssize_t receivedBytes = recvfrom(m_socket, &datagram, MAX_DATAGRAM_SIZE, 0, (struct sockaddr*)&sen_addr, &len);
            if (receivedBytes < 0) 
            {
                perror("\033[1;31m SOCKET 8082: \033[0m\n");
                return;
            }

            reply.error = htonl(0);
            reply.magic = htonl(NBD_REPLY_MAGIC);
            memcpy(reply.handle, (char*)&datagram.m_handle, sizeof(reply.handle));

            std::cout << ">>>>>> " << reply.handle << " <<<<<<" << std::endl;
            receivedData.insert(receivedData.end(), datagram.m_data, datagram.m_data + (receivedBytes - HEADER));

            std::cout << "I get from minion  " << receivedData.size() << std::endl;

            if (receivedBytes < MAX_DATAGRAM_SIZE) 
            {
                if(datagram.m_size == receivedData.size())
                {
                    std::cout << "---Everything is OK!---" << std::endl;

                    WriteOnFD(FD, (char*)&reply, sizeof(struct nbd_reply));
                    WriteOnFD(FD, receivedData.data(), receivedData.size());
                }
                else
                {
                    std::cout << "WRONG SIZE!" << std::endl;
                }

                std::cout << "Sended data size: " <<  datagram.m_size << std::endl;
                std::cout << "Received data size: " << receivedData.size() << std::endl;

                receivedBytes = 0;
                std::vector<char>(0).swap(receivedData);
                std::cout << "Final data size: " << receivedData.size() << std::endl;
                break;
            }
        }
    
    }

    int StaticListener::WriteOnFD(int fd, char* buf, size_t count)
    {
        size_t tmp = count;

        while (count > 0) 
        {
            int bytes_written = write(fd, buf, count);
            assert(bytes_written > 0);
            buf += bytes_written;
            count -= bytes_written;
        }
        assert(count == 0);

        return 0;
    }

    int StaticListener::GetFD()
    {
        return m_socket;
    }
}   
