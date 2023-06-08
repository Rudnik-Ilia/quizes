#pragma once

#include <fstream>
#include "Protocol.hpp"

namespace ilrd
{
    class Receiver
    {
        public:
            explicit Receiver(uint16_t port);
            ~Receiver();

            void Listen();
            int GetFD();
            void GetReadRequest(u_int64_t from, uint32_t size);

            void Send(std::shared_ptr<std::vector<char>> dataToSend, u_int64_t m_from, u_int64_t handle, uint32_t type);
            
        private:
            int m_sockfd;
            struct sockaddr_in receiverAddr;
            struct sockaddr_in senderAddr;
            std::fstream m_FILE;
            std::shared_ptr<std::vector<char>> m_data;
    };

    Receiver::Receiver(uint16_t port): m_FILE("/home/ilia53/git/prodjects/final_project/framework/test/txt.txt", std::ios::binary | std::ios::in | std::ios::out)
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
        receiverAddr.sin_port = htons(port); 
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
        
        auto receivedData = std::vector<char>(0);
        while (1)
        {
            while (1) 
            {
                Datagram datagram;
                Acknoledge ack;

                memset(&datagram, 0, sizeof(datagram));
                memset(&ack, 0, sizeof(ack));

                socklen_t senderAddrLen = sizeof(senderAddr);
            
                ssize_t receivedBytes = recvfrom(m_sockfd, &datagram, MAX_DATAGRAM_SIZE, 0, (struct sockaddr*)&senderAddr, &senderAddrLen);
                if (receivedBytes < 0) 
                {
                    std::cerr << "Error receiving data" << std::endl;
                }

                if(datagram.m_type == 33)
                {
                    std::cout<< "READING**********TASK" << std::endl;
                    std::cout<< "LEN: " << datagram.m_size << std::endl;

                    GetReadRequest(datagram.m_from, datagram.m_size);
                    Send(m_data, datagram.m_from, datagram.m_handle, 33);
                
                    // goto label_2;
                    break;
                    
                }

                receivedData.insert(receivedData.end(), datagram.m_data, datagram.m_data + (receivedBytes - HEADER));

                if (receivedBytes < MAX_DATAGRAM_SIZE) 
                {
                    if(datagram.m_size == receivedData.size())
                    {
                        std::cout << "---Everything is OK!---" << std::endl;
                        ack.m_code = CORRECT;

                        m_FILE.seekp(datagram.m_from);
                        m_FILE.write(receivedData.data(), receivedData.size());
                    }
                    else
                    {
                        std::cout << "WRONG SIZE!" << std::endl;
                        ack.m_code = ERROR;
                    }
                    std::cout << "Sended data size: " <<  datagram.m_size << std::endl;
                    std::cout << "Received data size: " << receivedData.size() << std::endl;

                    receivedBytes = 0;
                    std::vector<char>(0).swap(receivedData);
                    std::cout << "Final data size: " << receivedData.size() << std::endl;
    label_2:
                    ssize_t sentBytes = sendto(m_sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&senderAddr, sizeof(senderAddr));
                    if (sentBytes < 0) 
                    {
                        std::cerr << "Error sending data" << std::endl;
                    }
                    std::cout << "Sended ack: " << ack.m_code << std::endl;
                }
            }
        }
        
    }

    void Receiver::GetReadRequest(u_int64_t from, uint32_t size)
    {
        if(m_FILE.is_open())
        {
            auto buffer = std::make_shared<std::vector<char>>(size, 0); 
            m_FILE.seekg(from, std::ios::beg);
            m_FILE.read(buffer.get()->data(), size);
            std::cout<< "Reading.......... " <<  buffer.get()->size() << std::endl;
            
            m_data = buffer;
        }
    }

    void Receiver::Send(std::shared_ptr<std::vector<char>> dataToSend, u_int64_t m_from, u_int64_t handle, uint32_t type)
    {   
        Datagram datagram;        
        memset(&datagram, 0, sizeof(datagram));

        sockaddr_in SA;
        memset(&SA, 0, sizeof(SA));
        
        SA.sin_family = AF_INET;
        SA.sin_port = htons(1235); 
        SA.sin_addr.s_addr = INADDR_ANY;

        int m_second_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_sockfd < 0) 
        {
            std::cerr << "Error creating second socket" << std::endl;
        }

        int bufferSize = 64000;
        setsockopt(m_second_sockfd, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

        std::cout << "--------------------------" << std::endl;
        std::cout << "Size to send from minion: " << dataToSend->size() << std::endl;

        socklen_t len = sizeof(receiverAddr);
        size_t totalSentBytes = 0;

        while (totalSentBytes < dataToSend->size()) 
        {
            Datagram datagram;
            memset(&datagram, 0, sizeof(datagram));

            datagram.m_handle = handle;
            datagram.m_size = dataToSend->size();
            datagram.m_from = m_from;
            datagram.m_type = type;
            
            size_t dataLength = std::min((dataToSend->size() + HEADER) - totalSentBytes, MAX_DATAGRAM_SIZE);

            memcpy(&datagram.m_data, &(*dataToSend)[totalSentBytes], dataLength - HEADER);

            ssize_t sentBytes = sendto(m_second_sockfd, &datagram, dataLength, 0, (struct sockaddr*)&SA, sizeof(SA));
            if (sentBytes < 0) 
            {
                std::cerr << "Error sending data" << std::endl;
            }
            std::cout <<"sentBytes: " << sentBytes << std::endl;
            
            totalSentBytes += (sentBytes - HEADER);
            std::cout << "Sended bytes: " <<  totalSentBytes << std::endl;
        }
    }

    int Receiver::GetFD()
    {
        return m_sockfd;
    }
}
