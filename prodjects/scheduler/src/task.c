
#include <stdlib.h>
#include <assert.h>

#include "task.h"
#include "utils.h"



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
	task_t *new_task = (task_t*)malloc(sizeof(task_t));
	
	assert(NULL != task_func);
	
	
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
	new_task -> exec_time = time(0) + interval;
	
	return new_task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	free(task); 
}

int TaskExecute(task_t *task)
{
	assert(NULL != task);
	return task->task_func(task->params);
}

int TaskIsRepeating(task_t *task)
{
	assert(NULL != task);
	return task->is_repeated;
}
time_t TaskGetTime(task_t *task)
{
	assert(NULL != task);
	return task->exec_time;
}

ilrd_uid_t TaskGetUID(task_t *task)
{
	assert(NULL != task);
	return task->uid;
}

















