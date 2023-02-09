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

#define SEM_NAME "/semaphore"
#define SEM_NAME2 "/semaphore2"



int main()
{
    sem_t *sem = sem_open(SEM_NAME, 0);
    sem_t *sem2 = sem_open(SEM_NAME2, 0);

    if(sem == SEM_FAILED || sem == SEM_FAILED) 
    {
        fprintf(stderr, "sem_open() failed. errno: %d\n", errno);
        return 1;
    }

	while(1)
	{	
		printf("PONG\n");
		sleep(1);
        sem_post(sem);
        sem_wait(sem2);
	}

	return 0;
}

