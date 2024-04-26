#include "StaticListener.hpp"

namespace ilrd
{
    StaticListener::StaticListener()
    {
        memset(&rec_addr, 0, sizeof(struct sockaddr_in));
        memset(&sen_addr, 0, sizeof(struct sockaddr_in));
        
        m_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_socket < 0) 
        {
            std::cerr << "Error creating socket" << std::endl;
        }

        size_t bufferSize = MAX_DATAGRAM_SIZE;
        setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

        rec_addr.sin_family = AF_INET;
        rec_addr.sin_port = htons(1235); 
        rec_addr.sin_addr.s_addr = INADDR_ANY;
        
        struct timeval read_timeout;
        read_timeout.tv_sec = 0;
        read_timeout.tv_usec = 20;

        // setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);

        if(setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&read_timeout, sizeof(read_timeout)) < 0)
        {
            std::cerr << "Error setsockopt" << std::endl;
            throw("Set opt");
        }
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
        auto receivedData = std::vector<char>(0);
        int flag = 0;
        while(1) 
        {
            Datagram datagram;
            memset(&datagram, 0, sizeof(datagram));

            socklen_t len = sizeof(sen_addr);
        
            ssize_t receivedBytes = recvfrom(m_socket, &datagram, MAX_DATAGRAM_SIZE, 0, (struct sockaddr*)&sen_addr, &len);
            if (receivedBytes < 0) 
            {
                if(errno == EAGAIN || errno == EWOULDBLOCK) 
                {
                    std::cout << "\033[1;31m SOCKET 8082: TIMEOUT \033[0m\n" << std::endl;
                    return;
                }
                else
                {
                    std::cout << "\033[1;31m ERROR \033[0m\n" << std::endl;
                    return;
                }
            }
            else
            {
                receivedData.insert(receivedData.end(), datagram.m_data, datagram.m_data + (receivedBytes - HEADER));

                std::cout << "I get from minion  " << receivedData.size() << std::endl;

                if (receivedBytes < MAX_DATAGRAM_SIZE) 
                {
                    if(datagram.m_size == receivedData.size())
                    {
                        std::cout << "---Everything is OK!---" << std::endl;

                        struct nbd_reply reply;
                        reply.error = htonl(0);
                        reply.magic = htonl(NBD_REPLY_MAGIC);
                        memcpy(reply.handle, (char*)&datagram.m_handle, sizeof(reply.handle));

                        WriteOnFD(FD, (char*)&reply, sizeof(struct nbd_reply));
                        WriteOnFD(FD, receivedData.data(), receivedData.size());

                        break;
                    }
                    else
                    {
                        std::cout << "WRONG SIZE!" << std::endl;
                    }

                    std::cout << "Sended data size: " <<  datagram.m_size << std::endl;
                    std::cout << "Received data size: " << receivedData.size() << std::endl;

                    receivedBytes = 0;
                    std::vector<char>(0).swap(receivedData);
                }
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