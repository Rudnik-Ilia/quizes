
/* gd -pthread prod_cons_4.c ../../../ds/src/sll.c ../../../ds/src/queue.c -I ../../../ds/include */

#define _XOPEN_SOURCE  600  /*usleep*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h> 
#include "queue.h"
#include "SLL.h"
#include <errno.h>

#define SIZE (10)
#define CONSUMER (5)
#define PRODUCER (5)

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

queue_t *queue = NULL;

sem_t *sem_filled_cells;
sem_t *sem_free_cells;

void* Producer();
void* Consumer();


int main()
{
    size_t i = 0;
    size_t j = 0;

    pthread_t producer_threads[PRODUCER] = {0};
    pthread_t consumer_threads[CONSUMER] = {0};
    
    queue = QueueCreate();

    if(NULL == queue)
    {
        fprintf(stderr, "List creation failed. errno: %d\n", errno);
        return 1;
    }

    sem_filled_cells = sem_open("/sem_full" , O_CREAT, 0644, 0);
    sem_free_cells = sem_open("/sem_empty", O_CREAT, 0644, 10);

    if (sem_filled_cells  == SEM_FAILED || sem_free_cells == SEM_FAILED) 
    {
        fprintf(stderr, "Sem creation failed. errno: %d\n", errno);
        return 1;
    }    

    for(i = 0; i < PRODUCER; ++i)
    {
        pthread_create(&producer_threads[i], NULL, Producer, NULL);
    }
    for(j = 0; j < CONSUMER; ++j)
    {
        pthread_create(&consumer_threads[j], NULL, Consumer, NULL);
    }
    
  
    usleep(10000000);
    /* for(i = 0; i < NUMBEROFTHREADS; ++i)
    {
        pthread_join(producer_threads[i], NULL);
    }
    for(j = 0; j < NUMBEROFTHREADS; ++j)
    {
        pthread_join(consumer_threads[j], NULL);
    } */

    
    pthread_mutex_destroy(&mutex);
    sem_unlink("sem_full");
    sem_unlink("sem_empty");
    QueueDestroy(queue);
    return 0;
}

void *Producer()
{
    static volatile int data = 0;
    while (1)
    {
            sem_wait(sem_free_cells);
            pthread_mutex_lock(&mutex);

            data = __sync_add_and_fetch(&data, 1);
            QueueEnqueue(queue, *(void **)&data);
            sem_post(sem_filled_cells);
            printf("PUT %d\n", data);
    
            pthread_mutex_unlock(&mutex);
        
    }
    return NULL;
}


void *Consumer()
{
    void *data = NULL;
    while (1)
    {
        sem_wait(sem_filled_cells);
        pthread_mutex_lock(&mutex);

        data = QueuePeek(queue);
        QueueDequeue(queue);
        printf("TAKE: %d THE REST: %ld\n", *(int *)&data, QueueSize(queue));

        pthread_mutex_unlock(&mutex);
        sem_post(sem_free_cells);  
    }
    return NULL;
}