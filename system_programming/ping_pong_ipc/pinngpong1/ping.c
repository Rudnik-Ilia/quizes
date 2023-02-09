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

sem_t *sem;
sem_t *sem2;

int main(int argc, char *const argv[])
{
	pid_t child_pid = 0;
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 0);
    sem_t *sem2 = sem_open(SEM_NAME2, O_CREAT, 0644, 0);
	(void)argc;


    if(sem == SEM_FAILED || sem == SEM_FAILED) 
    {
        fprintf(stderr, "sem_open() failed. errno: %d\n", errno);
        return 1;
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
            sem_wait(sem);
			printf("PING\n");
			sleep(1);
            sem_post(sem2);
		}
		
	}
	return 0;
}


