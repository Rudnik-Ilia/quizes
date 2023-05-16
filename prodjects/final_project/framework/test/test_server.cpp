#include <vector>
#include "Sender.hpp"
#include "Protocol.hpp"

using namespace ilrd;

#define SIZE (4096)
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

    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};

    int udp_server_fd = 0;

    if (0 > (udp_server_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        fprintf(stderr, "Socket from Ctor failed. errno: %d\n", errno);
    }

    setsockopt(udp_server_fd, SOL_SOCKET, SO_RCVBUF, &MAX_SIZE, sizeof(MAX_SIZE));

    server_addr.sin_family = AF_INET;        
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; 
 
    if( 0 > (bind(udp_server_fd, (const struct sockaddr *)&server_addr, LENGHT)))
    {
        fprintf(stderr, "Bind from Ctor failed. errno: %d\n", errno);
    }

    std::string received_data;

    uint32_t expected_id = 0;
    bool stop_transmission = false;

    while(!stop_transmission)
    {
        Datagram datagram;

        int received_bytes = recvfrom(udp_server_fd, &datagram, sizeof(datagram), 0, (struct sockaddr*)&client_addr, &len); 
        if(received_bytes < 0)
        {
            fprintf(stderr, "recive from. errno: %d\n", errno);
        }
        std::cout << "Received data: " << datagram.m_data << std::endl;
        std::cout << "datagram.m_id: " << datagram.m_id << std::endl; 

        if (datagram.m_id == expected_id) 
        {
            received_data.append(datagram.m_data, received_bytes - sizeof(uint32_t));

            Datagram acknolege;
            acknolege.m_id = expected_id;

            int sended_bytes = sendto(udp_server_fd, &acknolege, sizeof(acknolege), 0, (struct sockaddr*)&client_addr, LENGHT);
            if(sended_bytes < 0)
            {
                fprintf(stderr, "send from. errno: %d\n", errno);
            }

            ++expected_id;

            std::cout << "RECIVED DATA SIZE: " << received_data.size() << '\n';
            std::cout << "received_bytes: " << received_bytes << '\n';
        }
        else
        {
            exit(1);
        }


        if (received_data.size() >= SIZE && received_bytes < sizeof(datagram)) 
        {
            stop_transmission = true;
        } 
        sleep(1);
    }


    
    return 0;
}
