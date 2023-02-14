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
        fprintf(stderr, "Something failed. errno: %d\n", errno);
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

void Create_UDP_Server()
{
    int udp_server_fd = 0;
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    socklen_t len = LENGHT;
    char buffer[SIZE] = {0};

    system("clear");
    system("fuser -k 1236/udp");

    Make_Socket(&udp_server_fd);
    Fill_Struct(&server_addr); 

    CheckValue(bind(udp_server_fd, (const struct sockaddr*)&server_addr, sizeof(server_addr)));
    
    while(1)
    {
        CheckValue(recvfrom(udp_server_fd, buffer, SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &len)); 
        fprintf (stderr, "server received %s\n", buffer);
        CheckValue(sendto(udp_server_fd, "pong", SIZE, MSG_CONFIRM, (const struct sockaddr*)&client_addr, LENGHT));
        fprintf (stderr, "server sent %s\n", buffer);  
        sleep(1);
    }
}