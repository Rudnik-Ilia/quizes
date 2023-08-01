#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h> /*SIGTERM*/
sem_t one;
sem_t two;

pthread_t pin;
pthread_t pon;

volatile int FLAG = 0;


void* Ping()
{
   while (1)
   {
        puts("PING");
        sleep(1);
        sem_post(&one);
        sem_wait(&two); 
   }
    return NULL;
}

void* Pong()
{
    while (1)
    {
        if(FLAG == 0)   
        {
            sem_wait(&one);
            FLAG = 1;
        }
        puts("PONG");
        sleep(1);
      
        sem_post(&two);
        sem_wait(&one);
    }
    return NULL;
}



int main()
{
    
    sem_init(&one, 0, 0);
    sem_init(&two, 0, 0);

    pthread_create(&pin, NULL, Ping, NULL);
    pthread_create(&pon, NULL, Pong, NULL);

    sleep(20);

    pthread_join(pin, NULL);
    pthread_join(pon, NULL);
    
    /*

    pthread_kill(pin, SIGTERM);
    pthread_kill(pon, SIGTERM);
    */


    return 0;
}