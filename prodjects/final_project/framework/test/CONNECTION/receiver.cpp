#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_DATAGRAM_SIZE 64000

struct Datagram 
{
    uint32_t m_id;
    char m_data[MAX_DATAGRAM_SIZE];
}__attribute__((packed));

int main() 
{
    system("clear");

    int sockfd;
    struct sockaddr_in receiverAddr, senderAddr;

    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
    {
        std::cerr << "Error creating socket" << std::endl;
    }

    int bufferSize = 65536;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(8080); 
    receiverAddr.sin_addr.s_addr = INADDR_ANY;

  
    if (bind(sockfd, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr)) < 0) 
    {
        std::cerr << "Error binding socket" << std::endl;
    }

    std::vector<char> receivedData;

    while (1) 
    {
        Datagram acknoledge;
        socklen_t senderAddrLen = sizeof(senderAddr);

        ssize_t receivedBytes = recvfrom(sockfd, &acknoledge, MAX_DATAGRAM_SIZE , 0, (struct sockaddr*)&senderAddr, &senderAddrLen);
        if (receivedBytes < 0) 
        {
            std::cerr << "Error receiving data" << std::endl;
            return 1;
        }

        receivedData.insert(receivedData.end(), acknoledge.m_data, acknoledge.m_data + receivedBytes);

        if (receivedBytes < MAX_DATAGRAM_SIZE) 
        {
            std::cout << "ID : " <<  acknoledge.m_id << std::endl;

            if(acknoledge.m_id == receivedData.size() - sizeof(uint32_t))
            {
                std::cout << "Everything is OK!" << std::endl;
            }
            std::cout << "Received data size: " << receivedData.size() << std::endl;
            std::cout << "DATA : " << receivedData.data() << std::endl;
            receivedBytes = 0;
            receivedData.clear();
            std::cout << "Final data size: " << receivedData.size() << std::endl;
        }
    }

    close(sockfd);

    return 0;
}
   
