#define _POSIX_C_SOURCE 200112L

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <SLL.h>
#include <alloca.h>
#include <errno.h>

#define SIZE (10)
#define NUMBEROFTHREADS (20)

sll_t *list;
volatile int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

void* Producer(void *dat);
void* Consumer(void *dat);

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

    if(0 != sem_init(&sem, 0, 0))
    {
        fprintf(stderr, "Sem_init creation failed.. errno: %d\n", errno);
        return 1;
    }


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
    sem_destroy(&sem);
    SllDestroy(list);
    
    return 0;
}

void* Producer(void *dat)
{   
    int data = 0;
    pthread_mutex_lock(&mutex);
    data = __sync_add_and_fetch(&data, 1);
    
    SllInsert(SllBegin(list), *(void **)&data);
    printf("PUT: %d\n", data);

    sem_post(&sem);
    pthread_mutex_unlock(&mutex);

    return dat;
}

void* Consumer(void *dat)
{
    int data = 0;
    sem_wait(&sem);
    pthread_mutex_lock(&mutex);

    data = (size_t)SllGetData(SllBegin(list));

    SllRemove(SllBegin(list));
    printf("TAKE: %d\n", data);

    pthread_mutex_unlock(&mutex);

    return dat;
}
