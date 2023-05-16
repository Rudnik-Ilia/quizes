#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_DATAGRAM_SIZE (size_t)64000

struct Datagram 
{
    uint32_t m_id;
    char m_data[MAX_DATAGRAM_SIZE];
}__attribute__((packed));

int main() 
{
    // system("clear");

    int sockfd;
    struct sockaddr_in receiverAddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(8080); 
    receiverAddr.sin_addr.s_addr = INADDR_ANY;

    std::vector<char> dataToSend(186, 'T');

    size_t totalSentBytes = 0;

    while (totalSentBytes < dataToSend.size()) 
    {
        Datagram datagram;
        datagram.m_id = dataToSend.size();
        size_t dataLength = std::min(dataToSend.size() - totalSentBytes, MAX_DATAGRAM_SIZE);

        memcpy(&datagram.m_data, &dataToSend[totalSentBytes], dataLength);

        ssize_t sentBytes = sendto(sockfd, &datagram, dataLength + sizeof(uint32_t), 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
        if (sentBytes < 0) 
        {
            std::cerr << "Error sending data" << std::endl;
            return 1;
        }

        totalSentBytes += sentBytes;
    }

    close(sockfd);

    return 0;
}