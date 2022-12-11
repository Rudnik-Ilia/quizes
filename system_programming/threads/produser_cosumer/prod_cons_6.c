/* gd -pthread prod_cons_6.c */

#define _XOPEN_SOURCE  600  /*usleep*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h> 
#include <signal.h>
#include <errno.h>

#define COLOR "\033[1;31m" 
#define OFFCOLOR "\033[0m" 

#define SIZE (10)
#define PRODUCER (1)
#define CONSUMER (5)
#define BIGPART (1450080000000L)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

sem_t *sem;
volatile unsigned int STAFF = 0;

void *Producer();
void *Consumer();

int main()
{
    size_t i = 0;
    size_t j = 0;

    pthread_t producer_threads[PRODUCER] = {0};
    pthread_t consumer_threads[CONSUMER] = {0};

    sem = sem_open("/sem" , O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) 
    {
        fprintf(stderr, "Sem creation failed. errno: %d\n", errno);
        return 1;
    }    
   
    if(pthread_create(&producer_threads[i], NULL, Producer, NULL) != 0)
    {
        return 1;
    }
    

    for(j = 0; j < CONSUMER; ++j)
    {
        if(pthread_create(&consumer_threads[j], NULL, Consumer, NULL) != 0)
        {
            return 1;
        }
    }

    pthread_join(producer_threads[0], NULL);

    for(i = 0; i < CONSUMER; ++i)
    {
        sem_post(sem);
    }
    pthread_cond_broadcast(&condition);

    usleep(10000);



    for(i = 0; i < PRODUCER; ++i)
    {
        pthread_kill(producer_threads[i], SIGTERM);
    }

    for(j = 0; j < CONSUMER; ++j)
    {
        pthread_kill(consumer_threads[i], SIGTERM);
    }  

    pthread_mutex_destroy(&mutex);
    sem_unlink("/sem");
    pthread_cond_destroy(&condition);

    return 0;
}


void *Producer()
{	
	int i = 0;
	int sem_value;
    int status = 0;

    while(1)
    {   
        STAFF = CONSUMER;
        sem_getvalue(sem, &sem_value);
        if(sem_value == CONSUMER)
        {
            for(i = 0; i < CONSUMER; ++i)
            {
                sem_wait(sem);
            }
            if(!(status = pthread_mutex_lock(&mutex)))
            {
                printf(COLOR"PUT: %d\n"OFFCOLOR, STAFF);
                pthread_cond_broadcast(&condition);
                pthread_mutex_unlock(&mutex);
            }
        }

    }
    

	return NULL;
}

void *Consumer()
{	 	
	int status = 0;

    while(1)
    {
        if(!(status = pthread_mutex_lock(&mutex)))
        {
            sem_post(sem);
            pthread_cond_wait(&condition, &mutex);
            --STAFF;
            printf("TAKE: %d I AM: %ld\n", STAFF, pthread_self());
            pthread_mutex_unlock(&mutex);
        }
    }
	return NULL;
}

/* void *Producer()
{
    size_t i = 0;
    int val = 0;

    while (1)
    {
        sem_getvalue(sem, &val); 

        if(val == CONSUMER)
        {

            STAFF = CONSUMER;
            pthread_mutex_lock(&mutex);
            printf(COLOR"PUT: %d\n"OFFCOLOR, STAFF);
            pthread_mutex_unlock(&mutex);

            for (i = 0; i < CONSUMER; ++i)
            {                                               
                sem_post(sem);
            }
        
        }
        pthread_cond_broadcast(&condition);
        
    }

    return NULL;
}

void *Consumer()
{
    while (1)
    {
        sem_wait(sem);
        pthread_mutex_lock(&mutex);
        printf("TAKE: %u I AM THREAD: %ld\n", STAFF, pthread_self());
        STAFF--;
        pthread_cond_wait(&condition, &mutex);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
} */