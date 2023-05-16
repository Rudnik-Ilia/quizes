#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>

#define MAX_DATAGRAM_SIZE (size_t)(1024)

#define MAX_RETRIES (30)

struct Datagram {
    uint32_t sequenceNumber;
    char data[MAX_DATAGRAM_SIZE];
};

int main() 
{
    system("clear");

    int sockfd;
    struct sockaddr_in receiverAddr;

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

    std::string data = "This is the data to be sent";

    size_t dataSize = data.size();

    size_t numDatagrams = (dataSize + MAX_DATAGRAM_SIZE - 1) / MAX_DATAGRAM_SIZE;

    size_t bytesSent = 0;
    uint32_t sequenceNumber = 0;
    size_t retries = 0;

    while (bytesSent < dataSize) 
    {
        size_t remainingData = dataSize - bytesSent;
        size_t datagramSize = std::min(remainingData, MAX_DATAGRAM_SIZE);

        Datagram datagram;

        datagram.sequenceNumber = sequenceNumber;

        std::memcpy(datagram.data, data.substr(bytesSent, datagramSize).c_str(), datagramSize);

        ssize_t sentBytes = sendto(sockfd, &datagram, sizeof(datagram), 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
        if (sentBytes < 0) 
        {
            fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
        }

        Datagram ack;

        ssize_t receivedBytes = recv(sockfd, &ack, sizeof(ack), 0);
        if (receivedBytes < 0) 
        {
            fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
        }

        if (ack.sequenceNumber == sequenceNumber) 
        {
            bytesSent += datagramSize;
            sequenceNumber++;
            retries = 0;
            
        } 
        else 
        {
            // Resend the datagram if acknowledgment mismatch or timeout
            
            retries++;
            if (retries > MAX_RETRIES) {
                std::cerr << "Max retries exceeded. Aborting transmission." << std::endl;
                return 1;
            }
        }
    }

    close(sockfd);

    return 0;
}