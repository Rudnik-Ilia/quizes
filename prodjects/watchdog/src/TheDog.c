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

#define NO (void)
char *path1 = "./user";

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
    struct sigaction user1 = {0};
    struct sigaction user2 = {0};
    sched_t *sched = SchedCreate();

    NO(argc);
    

    user1.sa_handler = Handler_1;
    user1.sa_flags = 0;
    sigemptyset(&user1.sa_mask);
    sigaction(SIGINT, &user1, NULL);

    user1.sa_handler = Handler_2;
    user1.sa_flags = 0;
    sigemptyset(&user2.sa_mask);
    sigaction(SIGINT, &user2, NULL);

    signal(SIGINT,Handler_2);

    if(NULL == sched)
    {
        write(1, "SCHED CRASHED FROM DOG\n", 24);
        return 1;

    }

    SchedAddTask(sched, 3, 1, Signal, argv);
    SchedAddTask(sched, 9, 1, Check, argv);
    SchedAddTask(sched, 1, 1, Stop, sched);

    SchedRun(sched);
    puts("Sched stop!");

    SchedDestroy(sched);
    puts("Sched destroy!");

    return 0;
}

/*********************TASKS************************************/

int Signal(void *data)
{
    write(1, "SIGNAL FROM DOG\n", 16);
    NO(data);
   /*  kill(getppid(), SIGUSR1); */
    return 0;
}

int Check(void *data)
{
    write(1, "CHECK FROM DOG\n", 15);

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
    write(1, "STOP FROM DOG\n", 14);
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
    
    if(sig == SIGINT)
    {
        ISLIFE = 1;
    }
}

void Handler_2(int sig)
{
    write(1, "HANDLER 2 FROM DOG\n", 21);

    if(sig == SIGINT)
    {
        STOPFLAG = 0;
    }
}

/****************************************************************/

void ReviveUser(void *data)
{   
    write(1, "REVIVING USER----------------\n", 30);
    /* execvp((char *)(data[1]), data); */
}