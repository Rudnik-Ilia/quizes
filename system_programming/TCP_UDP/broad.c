#include <stdio.h> 
#include <string.h> 
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/ip.h> 
#include <unistd.h>    

#include "header.h"
int main(void)
{
    int sock_fd = 0;
    struct sockaddr_in broad_addr = {0};
    char *msg = "This message is for everyone";

    broad_addr.sin_family = AF_INET;                
    broad_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    broad_addr.sin_port = htons(PORT); 

    sock_fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, IPPROTO_UDP);
    if(sock_fd < 0)
    {
        perror("socket");
        return 1;
    }

    if (setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &broad_addr, sizeof(broad_addr)) == -1)
    {
        perror("setsockpot trouble");
        return -2;
    }

    while (1)
    {
        char buffer[SIZE] = {0};

        if (0 > sendto(sock_fd, "ping", SIZE, 0, (struct sockaddr *) &broad_addr, sizeof(broad_addr)))
        {
            perror("send");
            return 1;
        }
             
    }


    return 0;
}
