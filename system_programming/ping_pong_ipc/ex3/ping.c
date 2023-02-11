#define _POSIX_C_SOURCE 1
#include <fcntl.h>
#include <stdio.h>  
#include <string.h>  
#include <sys/types.h>  
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h> 
#include <stdlib.h>
#include <sys/stat.h>

#include "src.h"

int main(int argc, char *argv[])
{
	pid_t child_pid = 0;
	(void)argc;


    if (mkfifo(PIPE, 0777) == -1)
    {
        if(errno != EEXIST)
        {
            fprintf(stderr, "Pipe create failed. ping. errno: %d\n", errno);
            return 1;
        }
    }

	child_pid = fork();

	if(0 == child_pid)
	{
		execv(argv[1], argv);
	}
	if(0 < child_pid)
	{
		while(1)
		{   
            ReadWrite(PIPE, message_ping, 1);
		}
	}
	return 0;
}


