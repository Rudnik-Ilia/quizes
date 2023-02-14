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
    char buffer[SIZE]; 
    int nbytes = 0;
  
	Make_Socket(&sock_fd, 0);
	CheckValue(sock_fd);

	Fill_Struct(&servaddr);

    conn_fd = connect(sock_fd,(struct sockaddr*)&servaddr, LENGHT);
	CheckValue(conn_fd);

    while(1)
	{
		sprintf(buffer, "Ping");
		write(sock_fd, buffer, SIZE);
        printf("Sended message: '%s' from server\n", buffer);
		nbytes = read(sock_fd, buffer, SIZE);
		if (nbytes > 0) 
		{
		    buffer[nbytes] = 0;
		    printf("Received message: '%s' from server\n", buffer);
    	}
	}

}

