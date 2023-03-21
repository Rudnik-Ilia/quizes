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
      
        sem_post(&one);
        sem_wait(&two); 
   }
    
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
      
        sem_post(&two);
        sem_wait(&one);
    }
    
}
/*

void* Ping()
{
   while (1)
   {
       
        puts("PING");
        
        sem_wait(&two); 
        sem_post(&one);
   }
    
}

void* Pong()
{

    while (1)
    {
        sem_post(&two);
        puts("PONG");
        
        sem_wait(&one);
    }
    
}

*/
int main()
{
    
    sem_init(&one, 0, 0);
    sem_init(&two, 0, 0);

    pthread_create(&pin, NULL, Ping, NULL);
    pthread_create(&pon, NULL, Pong, NULL);

    sleep(20);

    pthread_kill(pin, SIGTERM);
    pthread_kill(pon, SIGTERM);


    return 0;
}