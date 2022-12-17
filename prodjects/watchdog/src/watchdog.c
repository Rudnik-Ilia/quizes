#define _POSIX_SOURCE
#define  _XOPEN_SOURCE
#define _POSIX_C_SOURCE 200112L

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

#define COLOR "\033[1;31m" 
#define OFFCOLOR "\033[0m"

#define SIZE_ENV (10)

char *PATH_TO_DOG = "./dog";

char PID[SIZE_ENV];

pid_t child_pid = 0;
pthread_t thread_of_sched;

volatile sig_atomic_t STOPFLAG = 1;
volatile sig_atomic_t ISLIFE = 1;

void *InitSched();
int Signal(void *data);
int Check(void *data);
int Stop(void *sched);
void Handler_1();
int ReviveDog(void *data);

wd_status_t KeepMeAlive(int argc, const char **argv, time_t interval, size_t threshold)
{
    struct sigaction user1 = {0};
    char **argument = {NULL};

    child_pid = fork();

    if(0 == child_pid)
    {
        puts("DOG WAS STARTED");
        execv(PATH_TO_DOG, argument);
    }
    if(0 < child_pid)
    {
        user1.sa_handler = Handler_1;
        user1.sa_flags = 0;
        sigemptyset(&user1.sa_mask);
        sigaction(SIGUSR1, &user1, NULL);

        puts("Im user on pause");

        pause();

        puts("Im user runnnnnning");

        if(0 != pthread_create(&thread_of_sched, NULL, InitSched, NULL))
        {
            return WD_PTHREAD_CREATE_FAILURE;
        }
    }
    else
    {
        return WD_FORK_FAILURE;
    }
    return 0;
}

void DoNotResuscitate()
{
    puts("SCHED WAS STOPPED by DNR");
    STOPFLAG = 0;
    kill(child_pid, SIGUSR2);
    pthread_join(thread_of_sched, NULL);
}

void *InitSched()
{
    sched_t *sched = SchedCreate();
    puts("START INIT SCHED FROM USER");
    if(NULL == sched)
    {
        return NULL;
    }

    SchedAddTask(sched, 3, 1, Signal, NULL);
    SchedAddTask(sched, 9, 1, Check, NULL);
    SchedAddTask(sched, 1, 1, Stop, sched);

    SchedRun(sched);
    SchedDestroy(sched);
    puts("Sched user destroy!");

    return NULL;

}

/*********************TASKS************************************/

int Signal(void *data)
{   
    NO(data);
    puts(COLOR"SIGNAL FROM USER"OFFCOLOR);
    kill(child_pid, SIGUSR1);
    return 0;
}

int Check(void *data)
{
    puts("CHECK FROM USER");
    
    if(1 == ISLIFE)
    {
        ISLIFE = 0;
        return 0;
    }
    return ReviveDog(data); 
}

int Stop(void *sched)
{
    puts("STOP from USER");    
    if(0 == STOPFLAG)
    {
        SchedStop((sched_t *)sched);
    }
    return 0;
}
/*******************HANDLERS***************************************/

void Handler_1()
{
    write(1, "HANDLER_1 FROM USER\n", 20);
    ISLIFE = 1;
    
}

int ReviveDog(void *data)
{
    pid_t tmp_pid = fork();
    char **argument = {NULL};
    puts("------------------------------REVIVING DOG");

    if(0 < tmp_pid)
    {
        kill(child_pid, SIGKILL);
        child_pid = tmp_pid;
    }
    if(0 == tmp_pid)
    {
        execv(PATH_TO_DOG, argument);
        puts("--------------------------TROOOOOOBLE!");
        return WD_EXEC_FAILURE;
    }
    if(0 > tmp_pid)
    {
        return WD_FORK_FAILURE;
    }
    return 0;
}

char *ParseArgs(int argc, const char **argv, time_t interval, size_t threshold)
{

}

