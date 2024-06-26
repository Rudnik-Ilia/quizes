#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200112L
#define  _XOPEN_SOURCE

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

#define COLOR "\033[1;33m" 
#define OFFCOLOR "\033[0m"

char *PATH = NULL;
pid_t PARENT = 0;

volatile sig_atomic_t WORKFLAG = 1;
volatile sig_atomic_t ISLIFE = 1;

int Signal(void *data);
int Check(void *data);
int Stop(void *sched);
void Handler_1();
void Handler_2();
int ReviveUser(void *data);

int main(int argc, char *argv[])
{
    int inter = 0;
    int thres = 0;
    int for_check = 0;

    sched_t *sched = NULL; 
    struct sigaction user1 = {0};
    struct sigaction user2 = {0};
    
    NO(argc);
    PARENT = getppid();

    printf("                                          DOG ID: %d  USER ID: %d\n", getpid(), getppid());
    printf("-------------%d\n", argc);
    

    PATH = argv[0];

    user1.sa_handler = Handler_1;
    user1.sa_flags = 0;
    sigemptyset(&user1.sa_mask);
    sigaction(SIGUSR1, &user1, NULL);

    user1.sa_handler = Handler_2;
    user1.sa_flags = 0;
    sigemptyset(&user2.sa_mask);
    sigaction(SIGUSR2, &user2, NULL);

    inter = atoi(getenv("INTERVAL"));
    thres = atoi(getenv("THRESHOLD")) * inter;

    sched = SchedCreate();
    if(NULL == sched)
    {
        return 1;
    }

    for_check = UIDIsSame(BadUID, SchedAddTask(sched, inter, 1, Signal, NULL)) + \
    UIDIsSame(BadUID, SchedAddTask(sched, thres, 1, Check, argv)) + \
    UIDIsSame(BadUID, SchedAddTask(sched, 1, 1, Stop, sched));

    if(for_check)
    {
        puts("TASK ERROR");
        return 1;
    }

    SchedRun(sched);
    SchedDestroy(sched);
    puts("Sched dog destroy!");

    return 0;
}

/*********************TASKS************************************/

int Signal(void *data)
{
    puts(COLOR"SIGNAL FROM DOG"OFFCOLOR);
    NO(data);
    kill(getppid(), SIGUSR1); 
    return 0;
}

int Check(void *data)
{
    puts("CHECK FROM DOG");
    if(ISLIFE == 1)
    {
        ISLIFE = 0;
        return 0;
    }
    return ReviveUser(data);
}

int Stop(void *sched)
{   
    puts("STOP FROM DOG");
    if(0 == WORKFLAG)
    {
        puts("TURN OFF DOG\n");
        SchedStop((sched_t *)sched);
    }
    return 0;
}
/*******************HANDLERS***************************************/

void Handler_1()
{
    write(1, "HANDLER_1 FROM DOG\n", 19);
    ISLIFE = 1; 
}

void Handler_2()
{
    write(1, "HANDLER_2 FROM DOG\n", 19);
    WORKFLAG = 0; 
}

/****************************************************************/

int ReviveUser(void *data)
{   
    size_t count = 0; 

    printf("%s ---------------------------------REVIVING USER\n", PATH);
    kill(PARENT, SIGKILL);
    while(-1 == execv(PATH,  (char**)data))
    {
        if(count == 10)
        {
            return WD_EXEC_FAILURE;
        }
        puts("TRY TO RESTORE USER");
        ++count;
        sleep(1);
    }
    puts("---------------------------------CAN'T CREATE");
    return WD_EXEC_FAILURE;
}