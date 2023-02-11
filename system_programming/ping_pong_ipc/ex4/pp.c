#include <stdio.h>     
#include <sys/types.h>  
#include <sys/ipc.h>    
#include <sys/msg.h>   
#include <unistd.h>     
#include <stdlib.h>   
#include <errno.h> 
#include <sys/wait.h>

#define SIZE 6

struct msgbuf 
{
    long mtype;   
    char mtext[SIZE];        
};

int main()
{
    key_t key = 0;
    int msqid = 0;
    pid_t pid = 0;
    size_t i = 0;
    struct msgbuf message = {1, "HELLO"};

    key = ftok("./myfile", 77);

    if(key < 0)
    {
        fprintf(stderr, "Key failed. errno: %d\n", errno);
        return 1;
    }

    msqid = msgget(key, 0777 | IPC_CREAT);

    if(msqid < 0)
    {
        fprintf(stderr, "MQ failed. errno: %d\n", errno);
        return 1;
    }

    pid = fork();

    if(0 == pid)
	{
		if (0 > msgsnd(msqid, &message, SIZE, 0))
        {
            fprintf(stderr, "MQ send. errno: %d\n", errno);
            return 1;
        }
        puts("I've sent and died!");
        return 0;
	}

    sleep(1);

    for (i = 0; i < 3; ++i)
    {
        pid = fork(); 

        if(0 == pid)
        {
            if (0 > msgrcv(msqid, &message, SIZE, 1, MSG_NOERROR))
            {
                fprintf(stderr, "MQ recieve. %ld errno: %d\n", i, errno);
                return 1;
            }

            printf("Im process %ld receive message: %s\n", i, message.mtext);
    
            if (0 > msgsnd(msqid, &message, SIZE, 0))
            {
                fprintf(stderr, "MQ send. %ld errno: %d\n", i,  errno);
                return 1;
            }
            return 0;
        }
        wait(NULL);
    }
    wait(NULL);
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}