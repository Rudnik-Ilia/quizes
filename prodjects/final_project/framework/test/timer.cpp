#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <stdio.h>  
#include <assert.h> 
#include <unistd.h> 

int expire_count = 0;


void timer_thread(__sigval_t sig) 
{
    pid_t tid = syscall(__NR_gettid);
    printf("timer thread id: %d, count: %d\n", tid, expire_count);
}

int main(int argc, char **argv) 
{
    pid_t tid = syscall(__NR_gettid);
    printf("main thread id: %d\n", tid);
    timer_t timer_id;

    struct sigevent sev;
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = timer_thread;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_value.sival_ptr = &timer_id;


    assert(timer_create(CLOCK_MONOTONIC, &sev, &timer_id) == 0);

    struct itimerspec its;

    its.it_interval.tv_sec = 4;
    its.it_interval.tv_nsec = 0;

    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;


    timer_settime(timer_id, 0, &its, NULL);

    printf("NEXT:' %d\n",  timer_gettime(timer_id, &its));


    sleep(10);
 
    timer_delete(timer_id);
    return 0;
}