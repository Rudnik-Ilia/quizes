
/* gd -pthread prod_cons_5.c ../../../ds/src/sll.c ../../../ds/src/queue.c -I ../../../ds/include */

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

#define COLOR "\033[1;31m" 
#define RESET "\033[0m" 

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

    usleep(50000);
    
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

    return 0;
}

void *Producer()
{
    static volatile int data = 0;

    while (1) 
    {
        sem_wait(sem_free_cells);

        pthread_mutex_lock(&prod_mutex);

        data = __sync_add_and_fetch(&data, 1);
        QueueEnqueue(queue, *(void **)&data);
        printf(COLOR"PUT: %d SIZE: %ld\n"RESET, *(int *)&data, QueueSize(queue));
        
        sem_post(sem_filled_cells);
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
        printf("TAKE: %d SIZE: %ld\n", *(int *)&data, QueueSize(queue));

        sem_post(sem_free_cells);
        pthread_mutex_unlock(&cons_mutex);
    }

    return NULL;
}