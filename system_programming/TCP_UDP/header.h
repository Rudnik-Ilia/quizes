#pragma once
#include <stdio.h>          
#include <arpa/inet.h>                              
#include <unistd.h>         
#include <stdlib.h>         
#include <errno.h>        
#include <string.h>

#define PORT (8383)
#define SIZE (4)
#define SO_REUSEPORT (1)
#define LENGHT sizeof(struct sockaddr_in)


void Fill_Struct(struct sockaddr_in *server_addr);
int Make_Socket(int *sock_fd);
void CheckValue(int val);

void Create_UDP_Client();
void Create_UDP_Server();