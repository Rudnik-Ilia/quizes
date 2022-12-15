#define _POSIX_SOURCE

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

char *path = "./dog";

pid_t child_pid = 0;
pthread_t thread_of_sched;

volatile sig_atomic_t STOPFLAG = 1;
volatile sig_atomic_t ISLIFE = 1;

void *InitSched();
int Signal(void *data);
int Check(void *data);
int Stop(void *sched);
void Handler_1(int sig);
void RevivedOG(void *data);

wd_status_t KeepMeAlive(int argc, const char **argv, time_t interval, size_t threshold)
{
    struct sigaction user1 = {0};
    char **argument = {NULL};
    

    child_pid = fork();

    if(0 == child_pid)
    {
        write(1, "DOG WAS STARTED\n", 16);
        execv(path, argument);
    }
    if(0 < child_pid)
    {
        user1.sa_handler = Handler_1;
        user1.sa_flags = 0;
        sigemptyset(&user1.sa_mask);
        sigaction(SIGUSR1, &user1, NULL);
        
        puts("Im on pause");

        pause();

        pthread_create(&thread_of_sched, NULL, InitSched, NULL);
    }
    else
    {/* TODO */ 
        return 1;
    }
    return 0;
}

void DoNotResuscitate()
{
    STOPFLAG = 0;
    kill(child_pid, SIGUSR2);
    pthread_join(thread_of_sched, NULL);

    write(1, "SCHED WAS STOPPED\n", 18);

}

void *InitSched()
{
    sched_t *sched = SchedCreate();
    write(1, "START INIT SCHED\n", 17);

    if(NULL == sched)
    {
        write(1, "SCHED CRASHED FROM USER\n", 24);
        return NULL;

    }

    SchedAddTask(sched, 3, 1, Signal, NULL);
    SchedAddTask(sched, 9, 1, Check, NULL);
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
    write(1, "I'M CHECK FROM DOG\n", 20);
    kill(child_pid, SIGUSR1);
    return 0;
}

int Check(void *data)
{
    write(1, "I'M CHECK FROM USER\n", 21);
    
    if(ISLIFE == 1)
    {
        ISLIFE = 0;
        return 0;
    }

    /* ReviveDog(data); */
    return 1;
}

int Stop(void *sched)
{
    if(0 == STOPFLAG)
    {
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

void ReviveDog(void *data)
{
    /* pid_t tmp_pid = fork();

    write(1, "REVIVING DOG\n", 15);

    if(0 == tmp_pid)
    {
        execvp(path, argv);
    }

    if(0 < tmp_pid)
    {
        kill(child_pid, SIGKILL);
        child_pid = temp_pid;
    }

    else
    {
        return 1;
    } */
}



