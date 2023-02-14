
#include <stdio.h>          
#include <sys/types.h>     
#include <unistd.h>       
#include <arpa/inet.h>     
#include <stdlib.h>                       
#include <errno.h>

#include "header.h"


int main()
{
    int udp_server_fd = 0;
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    socklen_t len = LENGHT;
    char buffer[SIZE] = {0};
    int nbytes;

    system("clear");
    system("fuser -k 1236/udp");

    Make_Socket(&udp_server_fd);
    Fill_Struct(&server_addr); 

    if(bind(udp_server_fd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        fprintf(stderr, "BIND failed. errno: %d\n", errno);
        return 1;
    }

    while(1)
    {
        nbytes = recvfrom(udp_server_fd, buffer, SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &len); 

        if (0 > nbytes)
        {
            puts("END CONNECTION!");
        }

        fprintf (stderr, "server received %s\n", buffer);
        puts(buffer);

        nbytes = sendto(udp_server_fd, "pong", SIZE, MSG_CONFIRM, (const struct sockaddr*)&client_addr, LENGHT);
        if (0 > nbytes)
        {
            puts("END CONNECTION!");
        }
        fprintf (stderr, "server sent %s\n", buffer);  
        sleep(1);
    }

    return 0;
}