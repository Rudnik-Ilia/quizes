#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/
#include <stdlib.h> /*abort*/
#include <sys/wait.h> /*wait*/
#include <pthread.h>

#include <watchdog.h>

pid_t child_pid = 0;
pthread_t thread_of_sched;
int STOPFLAG = 1;

wd_status_t KeepMeAlive(int argc, const char *argv[], time_t interval, size_t threshold)
{
    struct sigaction user1 = {0};

    child_pid = fork();

    if(0 == child_pid)
    {
        execv();
    }
    if(0 < child_pid)
    {
        user1.sa_handler = Handler_1;
        user1.sa_flags = 0;
        sigemptyset(&user1.sa_mask);
        sigaction(SIGUSR1, &user1, NULL);

        pause();
        
        pthread_create(thread_of_sched, NULL, InitSched, NULL);
    }
    else
    {/* TODO */ 
        return 1;
    }

}

void DoNotResuscitate()
{

}

int Handler_1()
{

}

int InitSched()
{
    sched_t *sched = SchedCreate();

    SchedAddTask();
    SchedAddTask();
    SchedAddTask();
    SchedRun();

    SchedDestroy();

    return 0;
}

int Signal()
{
    kill(child_pid, SIGUSR1);
    return 0;

}

void Check()
{

}

int Stop(sched_t *sched)
{
    if(0 == STOPFLAG)
    {
        SchedStop();
    }
    return 0;
}