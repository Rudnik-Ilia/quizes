
#include "task.h"



struct task
{
    int (*task_func)(void *params);
    void *params;
    int is_repeated;
    ilrd_uid_t uid;
    time_t interval;
    time_t exec_time;
};

