#define _POSIX_C_SOURCE 200112L

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <SLL.h>

#define NUMBEROFTHREADS (5)
#define SIZE (10)

sll_t *list;
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
        pthread_create(&producer_threads[i], NULL, Producer, NULL);
        pthread_create(&consumer_threads[i], NULL, Consumer, NULL);
    }

    for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_join(producer_threads[0], NULL);
        pthread_join(consumer_threads[0], NULL);
    }
  
    
    return 0;
}

void* Producer()
{
    while (1)
    {
    
        
    }
    
}

void* Consumer()
{
    while (1)
    {
   
        
    }
}