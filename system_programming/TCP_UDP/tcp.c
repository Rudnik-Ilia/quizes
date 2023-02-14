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

#include "header.h"

int main()
{
	int sock_fd = 0;
    int conn_fd = 0;
    struct sockaddr_in servaddr = {0}; 
    socklen_t len = sizeof(servaddr);
    char buffer[SIZE]; 
    int nbytes = 0;

       
	sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock_fd < 0)
	{
		fprintf(stderr, "Sockfd failed. errno: %d\n", errno);
        return 1;
	}

	servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT); 
/*

    servaddr.sin_addr.s_addr = INADDR_ANY; 
*/

    if (inet_aton("127.0.0.1", &servaddr.sin_addr) == 0) 
    {
        perror("inet_aton");
        return 1;
    }


    conn_fd = connect(sock_fd,(struct sockaddr*)&servaddr, len);
	if(conn_fd < 0)
	{
		fprintf(stderr, "Connect failed. errno: %d\n", errno);
        return 1;
	}
    while(1)
	{
		sprintf(buffer, "Ping");

		write(sock_fd, buffer, SIZE);
		nbytes = read(sock_fd, buffer, SIZE);
		
		if (nbytes > 0) 
		{
		    buffer[nbytes] = 0;
		    printf("Received message: '%s' from server\n", buffer);
    	}
	}

}