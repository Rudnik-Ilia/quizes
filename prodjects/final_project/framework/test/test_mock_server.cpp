#include <linux/nbd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

#include "Protocol.hpp"


int main(int argc, char *argv[])
{   
    auto dataToSend = std::make_shared<std::vector<char>>(atoi(argv[1]), 'X');

    Datagram datagram;        
    memset(&datagram, 0, sizeof(datagram));

    struct sockaddr_in receiverAddr;
    struct sockaddr_in senderAddr;

    memset(&receiverAddr, 0, sizeof(struct sockaddr_in ));
    memset(&senderAddr, 0, sizeof(struct sockaddr_in ));

    sockaddr_in SA;
    memset(&SA, 0, sizeof(SA));
    
    SA.sin_family = AF_INET;
    SA.sin_port = htons(8082); 
    SA.sin_addr.s_addr = INADDR_ANY;

    int m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sockfd < 0) 
    {
        std::cerr << "Error creating MOCK socket" << std::endl;
    }

    int bufferSize = 64000;
    setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(bufferSize));

    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(8080); 
    receiverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_sockfd, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr)) < 0) 
    {
        std::cerr << "Error binding MOCK socket" << std::endl;
    }

    std::cout << "--------------------------" << std::endl;
    std::cout << "Size to send from MOCK minion: " << dataToSend->size() << std::endl;

    socklen_t len = sizeof(receiverAddr);
    size_t totalSentBytes = 0;

    while (totalSentBytes < dataToSend->size()) 
    {
        Datagram datagram;
        memset(&datagram, 0, sizeof(datagram));

        datagram.m_handle = 214474836492;
        datagram.m_size = dataToSend->size();
        datagram.m_from = 0;
        datagram.m_type = 0;
        
        size_t dataLength = std::min((dataToSend->size() + HEADER) - totalSentBytes, MAX_DATAGRAM_SIZE);

        memcpy(&datagram.m_data, &(*dataToSend)[totalSentBytes], dataLength - HEADER);

        ssize_t sentBytes = sendto(m_sockfd, &datagram, dataLength, 0, (struct sockaddr*)&SA, sizeof(SA));
        if (sentBytes < 0) 
        {
            std::cerr << "Error sending MOCK data" << std::endl;
        }
        std::cout <<"sentBytes MOCK : " << sentBytes << std::endl;
        
        totalSentBytes += (sentBytes - HEADER);
        std::cout << "Sended bytes MOCK : " <<  totalSentBytes << std::endl;
    }



    return 0;
}