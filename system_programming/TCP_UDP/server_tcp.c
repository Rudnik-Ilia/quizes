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
    socklen_t len = LENGHT;
    char buffer[SIZE]; 
    int nbytes = 0;

    system("clear");

	Make_Socket(&listen_fd, 0);
    CheckValue(listen_fd);
  
	Fill_Struct(&server_addr); 

	CheckValue(bind(listen_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)));

	listen(listen_fd,3);
 
    CheckValue(new_conn = accept(listen_fd, (struct sockaddr *) &client_addr, &len)); 
    
    
    while (1) 
    {
        nbytes = read(new_conn, buffer, SIZE);
        if(nbytes < 0)
        {

        }
        printf("Received message: '%s' from client\n", buffer);
        buffer[nbytes] = 0;
        sprintf(buffer, "Pong");
        write(new_conn, buffer, SIZE);
        printf("Send message: '%s' from client\n", buffer);
    }
		
}


