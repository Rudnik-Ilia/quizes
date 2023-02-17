#pragma once
#include <stdio.h>          
#include <arpa/inet.h>                              
#include <unistd.h>         
#include <stdlib.h>         
#include <errno.h>        
#include <string.h>

#define COLOR_red "\033[1;31m" 
#define COLOR_blue "\033[1;34m" 
#define OFFCOLOR "\033[0m" 

#define PORT (8080)
#define SIZE (5)
#define LENGHT sizeof(struct sockaddr_in)
#define SIZE_LOG_BUFF (60)
#define BACKLOG (3)

#define FD_COPY(dest,src) memcpy((dest),(src),sizeof *(dest))

extern socklen_t len;

void Fill_Struct(struct sockaddr_in *server_addr);
int Make_Socket(int *sock_fd, int x);
int CheckValue(int val, int line, char *name);
void Logger(char *str);

void Create_UDP_Client();

void Create_TCP_Client();

void Create_TCP_UDP_Server(int x_udp);

void Handler();
/*
#define SO_REUSEPORT (1)

void Create_UDP_Server();
void Create_TCP_Server();

*/