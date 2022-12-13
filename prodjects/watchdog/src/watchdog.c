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
    struct sigaction sig_user_1 = {0};

    child_pid = fork();

    if(0 == child_pid)
    {
        execv();
    }
    if(0 < child_pid)
    {
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

void Signal()
{

}

void Check()
{

}

void Stop()
{

}