#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h> 



int main() 
{
    pid_t pid = 0;

    char ping[] = "PING";
    char pong[] = "PONG";

    char *msg_to_send = NULL;

    char BUFF[5];

    int fd_ping[2] = {0};
    int fd_pong[2] = {0};

    int *fd = NULL;

    if (pipe(fd_ping) == -1 || pipe(fd_pong) == -1) 
    {
        fprintf(stderr, "Pipe fatal errno: %d\n", errno);
        return 1;
    }

    pid = fork();

    if(pid == 0) 
    {  
        msg_to_send = ping;
        fd = fd_ping;
       
    } 
    if(pid > 0)
    {  
        msg_to_send = pong;
        fd = fd_pong;
    }

     while (1)
    {
        sleep(1);

        if (0 > write(fd[1], msg_to_send, 5))
        {
            fprintf(stderr, "Write fail: %d\n", errno);
            return 1;
        }
        if (0 > read(fd[0], BUFF, 5))
        {
            fprintf(stderr, "Read fail: %d\n", errno);
            return 1;
        }

        puts(BUFF);
    
    }
    return 0;
}