#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#include <stdio.h>

#define SEM_1 "/SEM_1"
#define SEM_2 "/SEM_2"

int main()
{
    size_t i = 0;
    sem_t *sem1;
    sem_t *sem2;

    sem1 = sem_open(SEM_1, O_CREAT, 0666, 1);
    sem2 = sem_open(SEM_2, O_CREAT, 0666, 0);

    
    while(1)
    {
        sem_wait(sem2);
        puts("PONG");
        sleep(1);
        sem_post(sem1);
    }
    
    sem_unlink(SEM_1);
    sem_unlink(SEM_2);


    return 0;
}


