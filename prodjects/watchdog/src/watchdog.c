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

void *InitSched(void *data_args);
int Signal(void *data);
int Check(void *data);
int Stop(void *sched);
void Handler_1(int sig);
int ReviveDog(void *data);

wd_status_t KeepMeAlive(int argc, const char **argv, time_t interval, size_t threshold)
{
    struct sigaction user1 = {0};
    char **argument = {NULL};

    data_t *data_args = (data_t *)malloc(sizeof(data_t));
    if (data_args == NULL)
    {
        return 1;
    }

    data_args->argc = argc;
    data_args->argv = argv;
    data_args->interval = interval;
    data_args->threshold = threshold;

    sprintf(PID, "%d", getpid());
    putenv("DOGID=0");
    setenv("DOGID", PID, 1);

    child_pid = fork();

    if(0 == child_pid)
    {
        puts("DOG WAS STARTED");
        execv(PATH_TO_DOG, argument);
        return WD_EXEC_FAILURE;
    }
    if(0 < child_pid)
    {
        user1.sa_handler = Handler_1;
        user1.sa_flags = 0;
        sigemptyset(&user1.sa_mask);
        sigaction(SIGUSR1, &user1, NULL);

        
        sprintf(PID, "%d", getpid());
        putenv("DOGID=0");
        setenv("DOGID", "ilia", 1);

        puts("Im user on pause");
        pause();
        puts("Im user runnnnnning from pause");


        if(0 != pthread_create(&thread_of_sched, NULL, InitSched, data_args))
        {
            return WD_PTHREAD_CREATE_FAILURE;
        }
    }
    else
    {
        return WD_FORK_FAILURE;
    }
    return WD_SUCCESS;
}

void DoNotResuscitate()
{
    puts("SCHED WAS STOPPED by DNR");
    STOPFLAG = 0;
    kill(child_pid, SIGUSR2);
    pthread_join(thread_of_sched, NULL);
    return ;
}

void *InitSched(void *data_args)
{
    sched_t *sched = NULL;
    data_t *args_struct = NULL;
    time_t interval = 0;
    size_t threshold = 0;

    args_struct = (data_t*)data_args;
    interval = args_struct->interval;
    threshold = args_struct->threshold;

    puts("START INIT SCHED FROM USER");

    sched = SchedCreate();
    if(NULL == sched)
    {
        write(1, "SCHED CRASHED FROM USER\n", 24);
        return NULL;

    }

    SchedAddTask(sched, interval, 1, Signal, NULL);
    SchedAddTask(sched, (interval*threshold), 1, Check, NULL);
    SchedAddTask(sched, 1, 1, Stop, sched);

    SchedRun(sched);
    puts("Sched user stop!");

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
    return WD_SUCCESS;
}

int Check(void *data)
{
    puts("CHECK FROM USER");
    
    if(ISLIFE == 1)
    {
        ISLIFE = 0;
        return 0;
    }
    ReviveDog(data);
    return 0; 
}

int Stop(void *sched)
{
    puts("STOP FROM USER");
    if(0 == STOPFLAG)
    {
        puts("TURN OFF from USER");    
        SchedStop((sched_t *)sched);
    }
    return 0;
}
/*******************HANDLERS***************************************/
void Handler_1(int sig)
{
    write(1, "HANDLER 1 FROM USER\n", 21);

    if(sig == SIGUSR1)
    {
        ISLIFE = 1;
    }
}

int ReviveDog(void *data)
{
    pid_t tmp_pid = 0;
    char **argument = {NULL};

    puts("REVIVING DOG-------------------");

    tmp_pid = fork();
    
    if(0 == tmp_pid)
    {
        execv(PATH_TO_DOG, argument);
    }
    if(0 < tmp_pid)
    {
        kill(child_pid, SIGKILL);
        child_pid = tmp_pid;
    }
    else
    {
        return 1;
    } 
    return 0;
}



