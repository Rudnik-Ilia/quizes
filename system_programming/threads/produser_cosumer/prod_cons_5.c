
#define _XOPEN_SOURCE  600  /*usleep*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h> /* O_CREAT */
#include "queue.h"
#include <errno.h>




#define SIZE (10)
#define CONSUMER (3)
#define PRODUCER (3)

pthread_mutex_t prod_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cons_mutex = PTHREAD_MUTEX_INITIALIZER;

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
    sem_free_cells = sem_open("/sem_empty", O_CREAT, 0644, 1);

    if (sem_filled_cells  == SEM_FAILED || sem_free_cells == SEM_FAILED) 
    {
        fprintf(stderr, "Sem creation failed. errno: %d\n", errno);
        return 1;
    } 

    sem_wait(sem_free_cells);
        
    for(i = 0; i < PRODUCER; ++i)
    {
        pthread_create(&producer_threads[i], NULL, Producer, NULL);
    }
    for(j = 0; j < CONSUMER; ++j)
    {
        pthread_create(&consumer_threads[j], NULL, Consumer, NULL);
    }

    usleep(50000000);
    
    /* for(i = 0; i < PRODUCER; ++i)
    {
        pthread_cancel(producer_threads[i]);
    }
    for(j = 0; j < CONSUMER; ++j)
    {
        pthread_cancel(consumer_threads[j]);
    }  */

    pthread_mutex_destroy(&prod_mutex);
    pthread_mutex_destroy(&cons_mutex);

    sem_unlink("sem_full");
    sem_unlink("sem_empty");
    
    QueueDestroy(queue);

    return (0);
}


void *Producer()
{
    static volatile int data = 0;



    while (1) 
    {
         usleep(500);
        sem_wait(sem_free_cells);
        data = __sync_add_and_fetch(&data, 1);
        pthread_mutex_lock(&prod_mutex);

        QueueEnqueue(queue, *(void **)&data);
        
        sem_post(sem_free_cells);
        
        pthread_mutex_unlock(&prod_mutex);
    }

    return NULL;
}


void *Consumer()
{
    void *data = NULL;

    while (1)
    {
        sem_wait(sem_filled_cells);
        pthread_mutex_lock(&cons_mutex);

        data = QueuePeek(queue);
        QueueDequeue(queue);

        pthread_mutex_unlock(&cons_mutex);
        printf("cons say %d\n", *(int *)&data);
        sem_post(sem_free_cells);
    }

    return NULL;
}