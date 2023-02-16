#include <stdio.h>          /* printf */
#include <arpa/inet.h>      /* struct sockaddr_in, socket, htons, inet_pton
                                connect */
#include <unistd.h>         /* send, read */ 
#include <stdlib.h>         /* srand rand */
#include <time.h>           /* srand rand */

#define PORT (8080)
#define MSG_SIZE (5) 

void EndWithError(char *errorMessage);  /* External error handling function */

int main() 
{ 
    int sock = 0;
    struct sockaddr_in serv_addr = {0}; 
    int num_of_pings = 0;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sock) 
    { 
        EndWithError("socket");
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    if( 0 >= inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr))  
    { 
        EndWithError("inet_pton");
    } 
   
    if (0 > connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) 
    { 
        EndWithError("connect");
    } 

    srand(time(0)); 

    num_of_pings = rand() % 7;
    num_of_pings += 3;

    while (0 != num_of_pings)
    {
        char buffer[MSG_SIZE] = {0}; 

        --num_of_pings;

        if (0 > send(sock , "ping" , MSG_SIZE, 0))
        {
            EndWithError("send");
        }
        
        int valread = read(sock ,buffer , MSG_SIZE); 
        if (0 > valread)
        {
            EndWithError("read");
        }

        printf("%s\n", buffer); 

        sleep(num_of_pings);

    }
    return 0; 
} 

void EndWithError(char *errorMessage)  /* External error handling function */
{
    perror(errorMessage);
    exit(1);
}