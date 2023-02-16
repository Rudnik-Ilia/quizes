#pragma once
#include <stdio.h>          
#include <arpa/inet.h>                              
#include <unistd.h>         
#include <stdlib.h>         
#include <errno.h>        
#include <string.h>

#define PORT (8080)
#define SIZE (5)
#define LENGHT sizeof(struct sockaddr_in)

extern socklen_t len;

void Fill_Struct(struct sockaddr_in *server_addr);
int Make_Socket(int *sock_fd, int x);
int CheckValue(int val);

/*
#define SO_REUSEPORT (1)

void Create_UDP_Server();
void Create_TCP_Server();

*/

void Create_UDP_Client();

void Create_TCP_Client();


void Create_TCP_UDP_Server(int x_udp);