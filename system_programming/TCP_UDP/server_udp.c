
#include <stdio.h>          
#include <sys/types.h>     
#include <unistd.h>       
#include <arpa/inet.h>     
#include <stdlib.h>         
#include <string.h>         
#include <time.h>          
#include <errno.h>

#define PORT (1236)
#define SIZE (5)

int main()
{
    int udp_server_fd = 0;

    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};

    socklen_t addr_len = sizeof(struct sockaddr_in);

    char buffer[SIZE] = {0};
    int nbytes;

    system("clear");
    system("fuser -k 1236/udp");

    udp_server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;   

    if(bind(udp_server_fd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        fprintf(stderr, "BIND failed. errno: %d\n", errno);
        return 1;
    }
    while(1)
    {
        nbytes = recvfrom(udp_server_fd, buffer, SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &addr_len); 

        if (0 > nbytes)
        {
            puts("END CONNECTION!");
        }

        fprintf (stderr, "server received %s\n", buffer);
        puts(buffer);

        nbytes = sendto(udp_server_fd, "pong", SIZE, MSG_CONFIRM, (const struct sockaddr*)&client_addr, addr_len);
        if (0 > nbytes)
        {
            puts("END CONNECTION!");
        }
        fprintf (stderr, "server sent %s\n", buffer);  
        sleep(1);
    }

    return 0;
}