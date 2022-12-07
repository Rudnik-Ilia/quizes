#define _POSIX_C_SOURCE 200112L
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMBEROFTHREADS (2)
#define SIZE (10)


int STORAGE = 3;
pthread_spinlock_t lock;

void* Producer();
void* Consumer();

int main()
{
    pthread_t arr_of_threads[NUMBEROFTHREADS] = {0};

    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);

    pthread_create(&arr_of_threads[0], NULL, Producer, NULL);
    pthread_create(&arr_of_threads[1], NULL, Consumer, NULL);

    pthread_join(arr_of_threads[0], NULL);
    pthread_join(arr_of_threads[1], NULL);
  
    
    pthread_spin_destroy(&lock);
    
    return 0;
}

void* Producer()
{
    while (1)
    {
        puts("Start produce!");
        pthread_spin_lock(&lock);
        while(STORAGE < SIZE)
        {
            ++STORAGE;
            sleep(1);
            printf("PUSH STORE: %d\n", STORAGE);
        }
        pthread_spin_unlock(&lock);
        
    }
    
}

void* Consumer()
{
    while (1)
    {
        puts("Start consume!");
        pthread_spin_lock(&lock);
        while (STORAGE > 0)
        {
            --STORAGE;
            --STORAGE;
            sleep(1);
            printf("TAKE STORE: %d\n", STORAGE); 
        }
        pthread_spin_unlock(&lock);
        
    }
}