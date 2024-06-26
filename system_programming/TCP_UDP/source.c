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
    FILE *file = NULL;
    int lenght = strlen(str);
    int i = 0;
    char buffer[SIZE_LOG_BUFF];
    struct tm *newtime;
    int count = SIZE_LOG_BUFF - strlen(str);
    time_t ltime;
    time(&ltime);
    newtime = localtime(&ltime);

    file = fopen("./jornal.txt","a");
    if(file == NULL || lenght > SIZE_LOG_BUFF)
    {  
        exit(1);             
    }

    if(count)
    {
        memcpy(buffer, str, lenght);
        while (--count)
        {
            buffer[lenght + (i++)] = '.';
        }
        buffer[lenght + (i)] = '\0';
    }

    fprintf (file,"Event: %s  %s\n", buffer, asctime(newtime));
    fclose(file);
}

void Fill_Struct(struct sockaddr_in *server_addr)
{
    server_addr->sin_family = AF_INET;        
    server_addr->sin_port = htons(PORT);
    server_addr->sin_addr.s_addr = INADDR_ANY; 
}

int Make_Socket(int *sock_fd, int x)
{
    *sock_fd = socket(AF_INET,(x == 1 ? SOCK_DGRAM : SOCK_STREAM), 0);
    CheckValue(*sock_fd, __LINE__, __FILE__); 
    return 0;
}

int CheckValue(int val, int line, char *name)
{
    char buffer[100];
    if (0 > val)
    {   
        sprintf(buffer, "ERROR: %d LINE: %d FILE: %s", errno, line, name);
        Logger(buffer);
        fprintf(stderr, "Something failed. errno: %d\n", errno);
        return 1;
    }
    else if(0 == val)
    {
        return 3;
    }
    return 0;
}

void Create_UDP_Client()
{
    int sockfd = 0; 
    struct sockaddr_in server_addr = {0}; 
    char buffer[SIZE]; 
    int pings = 0;

    Make_Socket(&sockfd, 1);
    Fill_Struct(&server_addr);

    pings = rand() % 7;
    pings += 3;
    while (pings)
    {
        --pings;
        CheckValue(sendto(sockfd, "ping", SIZE, MSG_CONFIRM, (const struct sockaddr *) &server_addr, LENGHT), __LINE__, __FILE__); 
        printf("ping message sent.\n"); 
        CheckValue(recvfrom(sockfd, buffer, SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &len), __LINE__, __FILE__); 
        printf("Server : %s\n", buffer);
    }  
    close(sockfd); 
}

void Create_TCP_Client()
{
    int sock_fd = 0;
    struct sockaddr_in servaddr = {0}; 
    char buffer[SIZE]; 
    int nbytes = 0;
    int pings = 0;
  
	Make_Socket(&sock_fd, 0);
	Fill_Struct(&servaddr);

    CheckValue(connect(sock_fd,(struct sockaddr*)&servaddr, LENGHT), __LINE__, __FILE__);

    srand(time(0)); 

    pings = rand() % 7;
    pings += 3;

    while(pings)
	{
        --pings;
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
    close(sock_fd);
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
    CheckValue(listen_fd, __LINE__, __FILE__);
    Fill_Struct(&server_addr);
    CheckValue(bind(listen_fd, (struct sockaddr *)&server_addr, LENGHT), __LINE__, __FILE__);

    if(x_udp)
    {
        while(1)
        {
            CheckValue(recvfrom(listen_fd, buffer, SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &len), __LINE__, __FILE__); 
            fprintf(stderr, "server received %s\n", buffer);
            CheckValue(sendto(listen_fd, "pong", SIZE, MSG_CONFIRM, (const struct sockaddr*)&client_addr, LENGHT), __LINE__, __FILE__);
            fprintf(stderr, "server sent %s\n", buffer);  
            sleep(1);
        }
    }
    else
    {
        listen(listen_fd,3);
        CheckValue(new_conn = accept(listen_fd, (struct sockaddr *) &client_addr, &len), __LINE__, __FILE__);

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

void Handler()
{
    Logger("Exit by CTRL+C");
    puts("\n***STACK SMASHING DETECTED***");
    sleep(2);
    puts("Segmentation fault.");
    sleep(2);
    puts(COLOR_red"***KERNEL WARNING!!!***\n"OFFCOLOR);
    puts(COLOR_red"You need to restart your computer. Hold down the Power button for several seconds or press the Restart button.\n"OFFCOLOR);
    puts(COLOR_red"Veuillez redémarrer votre ordinateur. Maintenez la touche de démarrage enfoncée pendant plusieurs secondes ou bien appuyez sur le bouton de réinitialisation.\n"OFFCOLOR);
    puts(COLOR_red"Sie müssen Ihren Computer neu starten. Halten Sie dazu die Einschalttaste einige Sekunden gedrückt oder drücken.Sie die Neustart-Taste.\n"OFFCOLOR);
    sleep(100);
    exit(1);
}