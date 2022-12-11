
/* gd -pthread prod_cons_3.c ../../../ds/src/sll.c  -I ../../../ds/include  */

#define _XOPEN_SOURCE  600 /*usleep*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <signal.h> /*SIGTERM*/
#include <semaphore.h>
#include <fcntl.h> 
#include "SLL.h"
#include <errno.h>

#define SIZE (10)
#define CONSUMER (5)
#define PRODUCER (5)

#define COLOR "\033[1;31m" 
#define OFFCOLOR "\033[0m" 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t *sem;
sll_t *list;

void* Producer();
void* Consumer();

int main()
{
    size_t i = 0;
    size_t j = 0;

    pthread_t producer_threads[PRODUCER] = {0};
    pthread_t consumer_threads[CONSUMER] = {0};
    
    list = SllCreate();
    if(NULL == list)
    {
        fprintf(stderr, "List creation failed. errno: %d\n", errno);
        return 1;
    }

    sem = sem_open("/sem" , O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) 
    {
        fprintf(stderr, "Sem creation failed. errno: %d\n", errno);
        return 1;
    }    

    for(i = 0; i < PRODUCER; ++i)
    {
        if(pthread_create(&producer_threads[i], NULL, Producer, NULL) != 0)
        {
            return 1;
        }
    }
    for(j = 0; j < CONSUMER; ++j)
    {
        if(pthread_create(&consumer_threads[j], NULL, Consumer, NULL) != 0)
        {
            return 1;
        }
    }
  
    usleep(1000000);

    for(i = 0; i < PRODUCER; ++i)
    {
        pthread_kill(producer_threads[i], SIGTERM);
    }

    for(j = 0; j < CONSUMER; ++j)
    {
        pthread_kill(consumer_threads[i], SIGTERM);
    }

    pthread_mutex_destroy(&mutex);
    sem_unlink("sem");
    SllDestroy(list);
    
    return 0;
}

void *Producer()
{
    static volatile int data = 0;
    while (1)
    {
        data = __sync_add_and_fetch(&data, 1);
        pthread_mutex_lock(&mutex);

        usleep(1000);
        SllInsert(SllBegin(list), *(void **)&data);
        
        pthread_mutex_unlock(&mutex);
      
        sem_post(sem);
        printf(COLOR"PUT: %d\n"OFFCOLOR, data);
        
    }

    return NULL;
}


void *Consumer()
{
    void *data = NULL;
    iterator_t begin = NULL;

    while (1)
    {
        sem_wait(sem);
        pthread_mutex_lock(&mutex);

        begin = SllBegin(list);
        data = SllGetData(begin);
        SllRemove(begin);
        pthread_mutex_unlock(&mutex);
        usleep(100);
        printf("TAKE: %d\n", *(int *)&data);
    }

    return NULL;
}


