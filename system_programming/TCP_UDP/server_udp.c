
#include <stdio.h>          
#include <sys/types.h>     
#include <unistd.h>       
#include <arpa/inet.h>     
#include <stdlib.h>                       
#include <errno.h>

#include "header.h"


int main()
{
    system("clear");
    system("fuser -k 8383/udp");
    Create_UDP_Server();
    return 0;
}