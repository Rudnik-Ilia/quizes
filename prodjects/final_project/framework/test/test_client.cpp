#include <vector>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>
#include "Sender.hpp"
#include "Protocol.hpp"

using namespace ilrd;

#define SIZE (size_t)(4096)
#define PORT (8080)


int MAX_SIZE = 65536;

struct Datagram 
{
    uint32_t m_id;
    char m_data[SIZE];
}__attribute__((packed));

socklen_t len = LENGHT;

int main()
{
    system("clear");
    
    int sockfd = 0; 
    struct sockaddr_in server_addr = {0}; 

    if (0 > (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &MAX_SIZE, sizeof(MAX_SIZE));

    server_addr.sin_family = AF_INET;        
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; 

    std::string data_to_send = "This is the data to be sent";

    size_t size_of_data = data_to_send.size();

    size_t num_datagrams = (size_of_data + SIZE - 1) / SIZE;

    size_t sended_bytes = 0;
    uint32_t assign_id = 0;
    size_t retries = 0;

    while (sended_bytes < size_of_data)
    {
        size_t remain_to_send = size_of_data - sended_bytes;
        size_t size_of_datagram = std::min(remain_to_send, SIZE);

        Datagram datagram;
        datagram.m_id = assign_id;

        memcpy(datagram.m_data, data_to_send.substr(sended_bytes, size_of_datagram).c_str(), size_of_datagram);

        int sended_bytes = sendto(sockfd, &datagram, sizeof(datagram), 0, (struct sockaddr *)&server_addr, LENGHT); 
        if(sended_bytes < 0)
        {
            fprintf(stderr, "send from client. errno: %d\n", errno);
        } 

        Datagram acknolege;

        int received_bytes = recv(sockfd, &acknolege, sizeof(acknolege), 0);
        if(received_bytes < 0)
        {
            fprintf(stderr, "recive from. errno: %d\n", errno);
        }

        if (acknolege.m_id == assign_id) 
        {
            sended_bytes += size_of_datagram;
            ++assign_id;
            retries = 0;

            std::cout << "sended_bytes: " << sended_bytes << std::endl; 
            std::cout << "acknolege.m_id: " << acknolege.m_id << std::endl; 
            std::cout << "size_of_data:" << size_of_data << std::endl; 
        } 
        else 
        {   
            std::cout << "else "<< std::endl; 
            if (++retries > 3) 
            {
                std::cerr << "Max retries exceeded. Aborting transmission." << std::endl;
            }
        }

        std::cout << "From server :" << acknolege.m_data << std::endl; 
    } 

    close(sockfd); 

    std::cout << "END!" << std::endl; 

    return 0;
}