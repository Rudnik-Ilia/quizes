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

#include "header.h"

int main()
{
	int listen_fd = 0;
	struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    int new_conn = 0;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[SIZE]; 
    int nbytes = 0;

    system("clear");

	listen_fd = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if(listen_fd < 0)
    {
        perror("listen");
    }
  
	server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("10.10.1.187"); 


	if(0 > bind(listen_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)))
    {
        fprintf(stderr, " BIND failed. errno: %d\n", errno);
        system("fuser -k 8887/tcp");
        return 1;
    }
	listen(listen_fd,3);
        if ((new_conn = accept(listen_fd, (struct sockaddr *) &client_addr, &len)) == -1) 
        {
            perror("accept");
           
        }
    
     while (1) {
        
        nbytes = read(new_conn, buffer, SIZE);
        
        
        puts("----------------------");
        printf("Received message: '%s' from client\n", buffer);
        /*
        buffer[nbytes] = 0;
        sprintf(buffer, "Pong");
        
        write(new_conn, buffer, SIZE);
        close(new_conn);
        */
        
       
    }
		
}


