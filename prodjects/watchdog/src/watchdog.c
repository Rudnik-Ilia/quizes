#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/wait.h> 
#include <pthread.h>
#include <wd.h>

pid_t child_pid = 0;
pthread_t thread_of_sched;

int volatile STOPFLAG = 1;
int volatile ISLIFE = 1;

wd_status_t KeepMeAlive(int argc, const char *argv[], time_t interval, size_t threshold)
{
    struct sigaction user1 = {0};

    child_pid = fork();

    if(0 == child_pid)
    {
        write(1, "DOG WAS STARTED\n", 18);
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

void Handler_1(int sig)
{
    write(1, "HANDLER 1 FROM USER\n", 21);

    if(sig == SIGUSR1)
    {
        ISLIFE = 1;
    }
}

int InitSched()
{
    write(1, "START INIT SCHED\n", 18);

    sched_t *sched = SchedCreate();
    if(NULL == sched)
    {
        write(1, "SCHED CRASHED FROM USER\n", 25);
        return 1;

    }

    SchedAddTask(sched);
    SchedAddTask(sched);
    SchedAddTask(sched);
    SchedRun(sched);

    SchedDestroy(sched);

    return 0;
}

int Signal(void *data)
{
    kill(child_pid, SIGUSR1);
    return 0;
}

void Check(void *data)
{
    write(1, "I'M CHECK FROM USER\n", 21);
    
    if(ISLIFE == 1)
    {
        ISLIFE = 0;
        return 0;
    }
    ReviveDog();
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

void ReviveDog()
{
    pid_t tmp_pid = fork();

    if(0 == tmp_pid)
    {
        execv("/TheDog.c");
    }
    if(0 < tmp_pid)
    {
        kill(child_pid, SIGKILL);
        child_pid = temp_pid;
        pause();
    }
    else
    {
        return 1;
    }
}



