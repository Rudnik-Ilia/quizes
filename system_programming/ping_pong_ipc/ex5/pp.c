#include <stdio.h>      
#include <sys/types.h>  
#include <sys/ipc.h>    
#include <sys/shm.h>    /* shmat*/
#include <unistd.h>     /* fork */
#include <string.h>     /* memcpy */
#include <stdlib.h>      
#include <errno.h> 
#include <sys/wait.h>

#define SIZE 6

int main()
{
    key_t key = 0;
    int shmid = 0;
    pid_t pid = 0;
    size_t i = 0;
    char *message = NULL;

    key = ftok("./mymemory", 77);

    if(key < 0)
    {
        fprintf(stderr, "Key failed. errno: %d\n", errno);
        return 1;
    }

    shmid = shmget(key, SIZE, 0777 | IPC_CREAT);

    if(shmid < 0)
    {
        fprintf(stderr, "SHMGET. errno: %d\n", errno);
        return 1;
    }

    message = shmat(shmid, NULL, 0);
    if(*(int*)message < 0)
    {
        fprintf(stderr, "SHMAT. errno: %d\n", errno);
        return 1;
    }

    pid = fork();

    if(0 == pid)
	{
		memcpy(message, "HELLO", SIZE);
        puts("I've writen and died!");
        shmdt(message);
        return 0;
	}
    wait(NULL);

    for (i = 0; i < 3; ++i)
    {
        pid = fork(); 

        if(0 == pid)
        {
            printf("Im process %ld read message: %s\n", i, message);
            shmdt(message);
            return 0;
        }
        wait(NULL);
    }
    wait(NULL);


    shmctl(shmid, IPC_RMID, NULL);
    

    return 0;
}