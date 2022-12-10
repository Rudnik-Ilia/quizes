#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE  600  /*usleep*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMBEROFTHREADS (2)
#define SIZE (10)

#define COLOR "\033[1;31m" 
#define OFFCOLOR "\033[0m" 

int flag = 0;

int STORAGE = 3;
pthread_spinlock_t lock;

void* Producer();
void* Consumer();

int main()
{
    pthread_t arr_of_threads[NUMBEROFTHREADS] = {0};

    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);

    if(pthread_create(&arr_of_threads[0], NULL, Producer, NULL) != 0)
    {
        return 1;
    }
    if(pthread_create(&arr_of_threads[1], NULL, Consumer, NULL) != 0)
    {
        return 1;
    }

    usleep(100000);

    pthread_join(arr_of_threads[0], NULL);
    pthread_join(arr_of_threads[1], NULL);
  
    pthread_spin_destroy(&lock);
    
    return 0;
}

void* Producer()
{
    while (1)
    {
        pthread_spin_lock(&lock);
        while(STORAGE < SIZE)
        {
            if(flag == 0)
            {
                ++STORAGE;
                usleep(100);
                printf(COLOR"PUSH STORE: %d\n"OFFCOLOR, STORAGE);
            }
        }
        flag = 1;
        pthread_spin_unlock(&lock);
        
    }
    
}

void* Consumer()
{
    while (1)
    {
        pthread_spin_lock(&lock);
        while (STORAGE > 0)
        {
            if(flag != 0)
            {
                --STORAGE;
                usleep(100);
                printf("TAKE STORE: %d\n", STORAGE); 
            }
        }
        flag = 0;
        pthread_spin_unlock(&lock);
        
    }
}