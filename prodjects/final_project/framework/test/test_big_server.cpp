#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_DATAGRAM_SIZE (size_t)(1024)

struct Datagram 
{
    uint32_t sequenceNumber;
    char data[MAX_DATAGRAM_SIZE];
};

int main() 
{
    int sockfd;
    struct sockaddr_in receiverAddr, senderAddr;

 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
    }

    int bufferSize = 65536;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(8080); 
    receiverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr)) < 0) 
    {
        fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
    }

 
    std::string receivedData;

    uint32_t expectedSequenceNumber = 0;
    bool transmissionComplete = false;

    while (!transmissionComplete) 
    {
        Datagram datagram;
        socklen_t senderAddrLen = sizeof(senderAddr);

        ssize_t receivedBytes = recvfrom(sockfd, &datagram, sizeof(datagram), 0, (struct sockaddr*)&senderAddr, &senderAddrLen);
        if (receivedBytes < 0) 
        {
            fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
        }
     
        if (datagram.sequenceNumber == expectedSequenceNumber) 
        {
            receivedData.append(datagram.data, receivedBytes - sizeof(uint32_t));

            Datagram ack;
            ack.sequenceNumber = expectedSequenceNumber;
            
            ssize_t sentBytes = sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&senderAddr, sizeof(senderAddr));
            if (sentBytes < 0) 
            {
                fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
            }

            expectedSequenceNumber++;
        }

        if (receivedData.size() >= MAX_DATAGRAM_SIZE && receivedBytes < sizeof(datagram)) 
        {
            transmissionComplete = true;
        }
    }

    std::cout << "Received data: " << receivedData << std::endl;
    close(sockfd);

    return 0;
}