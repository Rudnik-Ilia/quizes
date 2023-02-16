#include <stdio.h>          
#include <arpa/inet.h>                              
#include <unistd.h>         
#include <stdlib.h>         
#include <errno.h>        
#include <string.h>
#include <time.h>   

#include "header.h"

socklen_t len = LENGHT;


void Logger(char *str)
{
    struct tm *newtime;
    time_t ltime;
    time(&ltime);
    newtime = localtime(&ltime);

    FILE *file;
    file = fopen("./jornal.txt","a");
    if(file == NULL)
    {  
        exit(1);             
    }
    fprintf (file, "Event: %s , %s\n", str, asctime(newtime));
    fclose(file);
}


void Fill_Struct(struct sockaddr_in *server_addr)
{
    (*server_addr).sin_family = AF_INET;        
    (*server_addr).sin_port = htons(PORT);
    (*server_addr).sin_addr.s_addr = INADDR_ANY; 
}

int Make_Socket(int *sock_fd, int x)
{
    *sock_fd = socket(AF_INET,(x == 1 ? SOCK_DGRAM : SOCK_STREAM), 0);
    if (0 > *sock_fd) 
    { 
        fprintf(stderr, "SOCKED failed. errno: %d\n", errno);
        return 1;
    }
    return 0;
}

int CheckValue(int val)
{
    if (0 > val)
    {
        fprintf(stderr, "Something failed. errno: %d\n", errno);
        return 1;
    }
    return 0;
}

void Create_UDP_Client()
{
    int sockfd = 0; 
    struct sockaddr_in server_addr = {0}; 
    char buffer[SIZE]; 

    Make_Socket(&sockfd, 1);
    Fill_Struct(&server_addr);

    while (1)
    {
        CheckValue(sendto(sockfd, "ping", SIZE, MSG_CONFIRM, (const struct sockaddr *) &server_addr, LENGHT)); 
        printf("ping message sent.\n"); 
        CheckValue(recvfrom(sockfd, buffer, SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &len)); 
        printf("Server : %s\n", buffer);
    }   
}

void Create_TCP_Client()
{
    int sock_fd = 0;
    struct sockaddr_in servaddr = {0}; 
    char buffer[SIZE]; 
    int nbytes = 0;
  
	Make_Socket(&sock_fd, 0);
	Fill_Struct(&servaddr);

    CheckValue(connect(sock_fd,(struct sockaddr*)&servaddr, LENGHT));
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

void Create_TCP_UDP_Server(int x_udp)
{
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    int listen_fd = 0;
    int new_conn = 0;
    char buffer[SIZE]; 
    int nbytes = 0;

    Make_Socket(&listen_fd, x_udp);
    CheckValue(listen_fd);
    Fill_Struct(&server_addr);
    CheckValue(bind(listen_fd, (struct sockaddr *)&server_addr, LENGHT));

    if(x_udp)
    {
        while(1)
        {
            CheckValue(recvfrom(listen_fd, buffer, SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &len)); 
            fprintf(stderr, "server received %s\n", buffer);
            CheckValue(sendto(listen_fd, "pong", SIZE, MSG_CONFIRM, (const struct sockaddr*)&client_addr, LENGHT));
            fprintf(stderr, "server sent %s\n", buffer);  
            sleep(1);
        }
    }
    else
    {
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
    

/*

void Create_UDP_Server()
{
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    int udp_server_fd = 0;
    char buffer[SIZE] = {0};

    Make_Socket(&udp_server_fd, 1);
    CheckValue(udp_server_fd);
    Fill_Struct(&server_addr); 
    CheckValue(bind(udp_server_fd, (const struct sockaddr*)&server_addr, LENGHT));
    
    while(1)
    {
        CheckValue(recvfrom(udp_server_fd, buffer, SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &len)); 
        fprintf(stderr, "server received %s\n", buffer);
        CheckValue(sendto(udp_server_fd, "pong", SIZE, MSG_CONFIRM, (const struct sockaddr*)&client_addr, LENGHT));
        fprintf(stderr, "server sent %s\n", buffer);  
        sleep(1);
    }
}


void Create_TCP_Server()
{
	struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    int listen_fd = 0;
    int new_conn = 0;
    char buffer[SIZE]; 
    int nbytes = 0;

	Make_Socket(&listen_fd, 0);
    CheckValue(listen_fd);
	Fill_Struct(&server_addr); 
	CheckValue(bind(listen_fd, (struct sockaddr *)&server_addr, LENGHT));

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
*/

}
