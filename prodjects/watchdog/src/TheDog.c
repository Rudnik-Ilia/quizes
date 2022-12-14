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

int STOPFLAG = 1;
int ISLIFE = 1;

int main()
{
    struct sigaction user1 = {0};

    user1.sa_handler = Handler_1;
    user1.sa_flags = 0;
    sigemptyset(&user1.sa_mask);
    sigaction(SIGUSR1, &user1, NULL);

    struct sigaction user2 = {0};

    user1.sa_handler = Handler_2;
    user1.sa_flags = 0;
    sigemptyset(&user2.sa_mask);
    sigaction(SIGUSR2, &user2, NULL);

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

void Handler_1()
{
    
}

void Handler_2()
{
    STOPFLAG = 0;
}

void ReviveUser()
{
    execv("./main.c");
}