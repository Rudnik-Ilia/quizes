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

char *path1 = "./user";

int volatile STOPFLAG = 1;
int volatile ISLIFE = 1;

int Signal(void *data);
int Check(void *data);
int Stop(void *sched);
void Handler_1(int sig);
void Handler_2(int sig);
void ReviveUser(void *data);

int main(int argc, const char *argv[])
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
    if(NULL == sched)
    {
        write(1, "SCHED CRASHED FROM DOG\n", 24);
        return 1;

    }

    SchedAddTask(sched, 5, 1, Signal, NULL);
    SchedAddTask(sched, 15, 1, Check, argv[1]);
    SchedAddTask(sched, 1, 1, Stop, NULL);
    SchedRun(sched);

    SchedDestroy(sched);

    return 0;
}

/*********************TASKS************************************/

int Signal(void *data)
{
    kill(child_pid, SIGUSR1);
    return 0;
}

int Check(void *data)
{
    write(1, "I'M CHECK FROM DOG\n", 21);

    if(ISLIFE == 1)
    {
        ISLIFE = 0;
        return 0;
    }
    ReviveUser();
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
    write(1, "REVIVING USER\n", 15);
    execv(path1, argv);
}