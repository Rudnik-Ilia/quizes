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

int main()
{
	while(1)
	{	
        ReadWrite(PIPE, message_pong, 0);
	}

	return 0;
}

