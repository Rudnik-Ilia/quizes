

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h> 
#include "SLL.h"
#include <errno.h>


#define SIZE (10)
#define NUMBEROFTHREADS (20)

sll_t *list;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t *sem;

void* Producer();
void* Consumer();

int main()
{
    size_t i = 0;

    pthread_t producer_threads[NUMBEROFTHREADS] = {0};
    pthread_t consumer_threads[NUMBEROFTHREADS] = {0};
    
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

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_create(&producer_threads[i], NULL, Producer, NULL);
    }
    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_create(&consumer_threads[i], NULL, Consumer, NULL);
    }
  
    sleep(2);

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_kill(producer_threads[0], SIGTERM);
    }

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_kill(consumer_threads[0], SIGTERM);
    }

    
    pthread_mutex_destroy(&mutex);
    sem_unlink(sem);
    SllDestroy(list);
    
    return 0;
}

void *Producer()
{
    int flag = 0;
    static volatile int data = 0;
    while (1)
    {
        data = (flag == 1) ? data: __sync_add_and_fetch(&data, 1);
        pthread_mutex_lock(&mutex);
        flag = (SllEnd(list) == SllInsert(SllBegin(list), *(void **)&data));
        pthread_mutex_unlock(&mutex);
        if (0 == flag)
        {
            sem_post(sem);
            printf("PUT: %d\n", data);
        }
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
        printf("TAKE: %d\n", *(int *)&data);
    }

    return NULL;
}


