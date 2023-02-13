#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <errno.h>

#define PORT (1234)
#define SIZE (5)

int main()
{
	int sock_fd = 0;
    int conn_fd = 0;
	
    struct sockaddr_in servaddr = {0}; 
    socklen_t len = sizeof(servaddr);
    char buffer[SIZE]; 
    int nbytes = 0;

    system("clear");
       
	sock_fd = socket(AF_INET, SOCK_STREAM,0);
	if(sock_fd < 0)
	{
		fprintf(stderr, "Sockfd failed. errno: %d\n", errno);
        return 1;
	}

	servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    conn_fd = connect(sock_fd,(struct sockaddr*)&servaddr, sizeof(servaddr));
	if(conn_fd<0)
	{
		fprintf(stderr, "Connect failed. errno: %d\n", errno);
        return 1;
	}

    while(1)
    {
      
	}	
}