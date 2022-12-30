#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t one;
sem_t two;

pthread_t pin;
pthread_t pon;

void* Ping()
{
   while (1)
   {
        puts("PING");
        sem_post(&one);
        sem_wait(&two); 
   }
    
}

void* Pong()
{

    while (1)
    {
        sem_wait(&one);
        puts("PONG");
        sem_post(&two);
    }
    
}


int main()
{
    
    sem_init(&one, 0, 0);
    sem_init(&two, 0, 0);

    pthread_create(&pin, NULL, Ping, NULL);
    pthread_create(&pon, NULL, Pong, NULL);

    sleep(10);

    pthread_join(pin, NULL);
    pthread_join(pon, NULL);


    return 0;
}