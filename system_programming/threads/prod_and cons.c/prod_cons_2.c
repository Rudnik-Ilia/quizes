#define _POSIX_C_SOURCE 200112L

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <SLL.h>
#include <alloca.h>

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
        pthread_create(&consumer_threads[i], NULL, Consumer, NULL);
        pthread_create(&producer_threads[i], NULL, Producer, NULL);
    }
  
    

    sleep(1);

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_join(producer_threads[0], NULL);
    }

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_join(consumer_threads[0], NULL);
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
            printf("TAKE: %d\n", *(int *)&data);
        }
        pthread_mutex_unlock(&mutex);
        
    }
}
