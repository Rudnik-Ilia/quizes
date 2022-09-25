
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

task_t *TaskCreate(ilrd_uid_t uid, int is_repeating, time_t interval, int (*task_func)(void *params), void *params)
{	
	assert(NULL != task_func);
	
	task_t *new_task = (task_t*)malloc(sizeof(task_t));
	
	if(NULL == new_task)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	new_task -> task_func = task_func;
	new_task -> params = params;
	new_task -> is_repeated;
	new_task -> uid = uid;
	new_task -> interval;
	new_task -> exec_time = 0;
	
	return new_task;
}

