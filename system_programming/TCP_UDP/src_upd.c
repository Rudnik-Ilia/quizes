#include <stdio.h>          
#include <arpa/inet.h>                              
#include <unistd.h>         
#include <stdlib.h>         
#include <errno.h>        
#include <string.h>
#include "header.h"


void Fill_Struct(struct sockaddr_in *server_addr)
{
    (*server_addr).sin_family = AF_INET;
    (*server_addr).sin_addr.s_addr = INADDR_ANY; 
    (*server_addr).sin_port = htons(PORT);
}

int Make_Socket(int *sock_fd)
{
    *sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > *sock_fd) 
    { 
        fprintf(stderr, "SOCKED failed. errno: %d\n", errno);
        return 1;
    }
}

void CheckValue(int val)
{
    if (0 > val)
    {
        puts("END CONNECTION!");
    }
}

void Create_UDP_Client()
{
    int sockfd = 0; 
    struct sockaddr_in server_addr = {0}; 
    socklen_t len = LENGHT;
    char buffer[SIZE]; 

    Make_Socket(&sockfd);
    Fill_Struct(&server_addr);

    while (1)
    {
        CheckValue(sendto(sockfd, "ping", SIZE, MSG_CONFIRM, (const struct sockaddr *) &server_addr, LENGHT)); 
        printf("ping message sent.\n"); 
        CheckValue(recvfrom(sockfd, buffer, SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &len)); 
        printf("Server : %s\n", buffer);
    }   
}
