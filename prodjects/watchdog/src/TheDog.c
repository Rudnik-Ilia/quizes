#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200112L
#define  _XOPEN_SOURCE

#include <signal.h>
#include <unistd.h> 
#include <sys/types.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/wait.h> 
#include <pthread.h>
#include <scheduler.h>
#include <wd.h>
#include "help.h"

#define COLOR "\033[1;33m" 
#define OFFCOLOR "\033[0m"

char *path = "./user";

volatile sig_atomic_t STOPFLAG = 1;
volatile sig_atomic_t ISLIFE = 1;

int Signal(void *data);
int Check(void *data);
int Stop(void *sched);
void Handler_1(int sig);
void Handler_2(int sig);
void ReviveUser(void *data);

int main(int argc, char *argv[])
{
    char *env = NULL;
    sched_t *sched = NULL; 
    struct sigaction user1 = {0};
    struct sigaction user2 = {0};
    
    NO(argc);

    env = getenv("DOGID");
    printf("@@@@@@@@ %s\n", env);

    printf("                               DOG ID: %d  USER ID: %d\n", getpid(), getppid());
    
    user1.sa_handler = Handler_1;
    user1.sa_flags = 0;
    sigemptyset(&user1.sa_mask);
    sigaction(SIGUSR1, &user1, NULL);

    user1.sa_handler = Handler_2;
    user1.sa_flags = 0;
    sigemptyset(&user2.sa_mask);
    sigaction(SIGUSR2, &user2, NULL);

    sched = SchedCreate();
    if(NULL == sched)
    {
        puts("SCHED CRASHED FROM DOG");
        return 1;

    }

    SchedAddTask(sched, 3, 1, Signal, argv);
    SchedAddTask(sched, 9, 1, Check, argv);
    SchedAddTask(sched, 1, 1, Stop, sched);

    SchedRun(sched);
    puts("Sched dog stop!");

    SchedDestroy(sched);
    puts("Sched dog destroy!");

    return 0;
}

/*********************TASKS************************************/

int Signal(void *data)
{
    puts(COLOR"SIGNAL FROM DOG"OFFCOLOR);
    NO(data);
    kill(getppid(), SIGUSR1); 
    return 0;
}

int Check(void *data)
{
    puts("CHECK FROM DOG");

    if(ISLIFE == 1)
    {
        ISLIFE = 0;
        return 0;
    }
    ReviveUser(data);
    return 0;
}

int Stop(void *sched)
{   
    puts("STOP FROM DOG");
    if(0 == STOPFLAG)
    {
        puts("TURN OFF DOG\n");
        SchedStop((sched_t *)sched);
    }
    return 0;
}
/*******************HANDLERS***************************************/

void Handler_1(int sig)
{
    write(1, "HANDLER 1 FROM DOG\n", 21);
    
    if(sig == SIGUSR1)
    {
        ISLIFE = 1;
    }
}

void Handler_2(int sig)
{
    write(1, "HANDLER 2 FROM DOG\n", 21);

    if(sig == SIGUSR2)
    {
        STOPFLAG = 0;
    }
}

/****************************************************************/

void ReviveUser(void *data)
{       
    char **argument = {NULL};
    puts("REVIVING USER----------------");
    execvp(path,  argument);
}