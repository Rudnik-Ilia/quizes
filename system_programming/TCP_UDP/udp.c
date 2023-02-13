#include <stdio.h>          
#include <arpa/inet.h>                              
#include <unistd.h>         
#include <stdlib.h>         
#include <time.h>  
#include <errno.h>        

#define PORT (1236)
#define SIZE (5) 


int main() 
{ 
    int sockfd = 0; 
    struct sockaddr_in server_addr = {0}; 
    socklen_t len = sizeof(server_addr);
    char buffer[SIZE]; 
    int nbytes = 0;

    system("clear");
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd) 
    { 
        fprintf(stderr, "SOCKED failed. errno: %d\n", errno);
        return 1;
    } 

    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(PORT); 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
      
    while (1)
    {
        nbytes = sendto(sockfd, "ping", SIZE, MSG_CONFIRM, (const struct sockaddr *) &server_addr, len); 
        if (0 > nbytes)
        {
            puts("END CONNECTION!");
        }

        printf("ping message sent.\n"); 

        nbytes = recvfrom(sockfd, buffer, SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &len); 
        if (0 > nbytes)
        {
            puts("END CONNECTION!");
        }
        
        printf("Server : %s\n", buffer);
    
    }
      
    return 0; 
} 