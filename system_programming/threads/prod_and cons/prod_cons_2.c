#define _XOPEN_SOURCE  600
#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h> /* O_CREAT */
#include "SLL.h"
#include <errno.h>


#define SIZE (10)
#define NUMBEROFTHREADS (5)

sll_t *list;
volatile int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* Producer();
void* Consumer();

int main()
{
    size_t i = 0;

    pthread_t producer_threads[NUMBEROFTHREADS] = {0};
    pthread_t consumer_threads[NUMBEROFTHREADS] = {0};
    
    list = SllCreate();

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        if(pthread_create(&producer_threads[i], NULL, Consumer, NULL))
        {
            return 1;
        }
    }
    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
         if(pthread_create(&consumer_threads[i], NULL, Consumer, NULL))
        {
            return 1;
        }
    }
  
    sleep(3);

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_kill(producer_threads[0], SIGTERM);
    }

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_kill(consumer_threads[0], SIGTERM);
    }

    pthread_mutex_destroy(&mutex);
    SllDestroy(list);
    
    return 0;
}

void* Producer()
{   
    int data = 0;

    while (1)
    {
        pthread_mutex_lock(&mutex);
        if(1)
        {
            data = __sync_add_and_fetch(&data, 1);
            
            SllInsert(SllBegin(list), *(void **)&data);
            usleep(5000);
            printf("PUT: %d\n", data);
        }
        pthread_mutex_unlock(&mutex);
        
    }
    
}

void* Consumer()
{
    void *data = NULL;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if(!SllIsEmpty(list))
        {
            data = SllGetData(SllBegin(list));
            SllRemove(SllBegin(list));
            usleep(500);
            printf("TAKE: %d\n", *(int *)&data);
        }
        pthread_mutex_unlock(&mutex);
        
    }
}
