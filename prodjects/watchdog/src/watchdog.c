#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/wait.h> 
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
        write(1, "DOG WA\n", 19);
        execv("./TheDog.out");
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
    STOPFLAG = 0;
    kill(child_pid, SIGUSR2);
    pthread_join(thread_of_sched, NULL);

    write(1, "SCHED WAS STOPPED\n", 19);

}

int Handler_1()
{

}

int InitSched()
{
    write(1, "START INIT SCHED\n", 18);

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

void ReviveDog()
{
    execv("/TheDog.c");
}