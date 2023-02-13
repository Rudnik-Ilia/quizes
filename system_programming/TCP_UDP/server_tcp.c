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

#define PORT 1234

int main(int argc, char *argv[])
{
	int listenfd=0,connfd=0;
	struct sockaddr_in servaddr = {0};

	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
  

	servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
   	
    serveraddr.sin_addr.s_addr = INADDR_ANY; 

	bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    
	listen(listenfd,3);

    connfd = accept(listenfd,(struct sockaddr *)NULL, NULL);

    printf("Hello\n");
    while(1)
    {
        scanf("%s",sendBuff);
        write(connfd,sendBuff,1000);
        read(connfd,s,1000);
        printf("\nclient : %s\n",s);
    }
		
		close(connfd);
}