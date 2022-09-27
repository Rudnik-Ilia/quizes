
/**********************
* Title : SCHEDULER
* Author: Ilia Rudnik
* Reviewer: 
* Date : 20/09/2022
* Status : approved
***********************/


#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include <unistd.h> /* getpid */
#include "scheduler.h"


#include "pqueue.h"
#include "task.h"
#include "utils.h"


struct scheduler
{
    pq_t *tasks;
    int is_running;
};


static int CompareTime(const void *tsk1, const void *tsk2)
{
	assert(NULL != tsk1);
	assert(NULL != tsk2);
	return TaskGetTime((task_t *)tsk1) - TaskGetTime((task_t *)tsk2); 
	/*
	return TaskGetTime((task_t *)tsk1) == TaskGetTime((task_t *)tsk2);
	*/
}

static int CompareUID(const void *task, void *uid)
{	
	assert(NULL != task);	
	return UIDIsSame(TaskGetUID((task_t*)task), *(ilrd_uid_t*)uid);
}

sched_t *SchedCreate(void)
{
	sched_t *new_sched = (sched_t*)malloc(sizeof(sched_t));
	if(NULL == new_sched)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}	
	
	new_sched -> tasks = PQCreate(CompareTime);
	if(NULL == new_sched-> tasks)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(new_sched);
		return NULL;
	}
	new_sched -> is_running = 0;

	return new_sched;
}


ilrd_uid_t SchedAddTask(sched_t *sched, time_t interval_in_sec, int is_repeating, int (*task_func)(void *params), void *params)
{	
	 
	ilrd_uid_t new_uid = UIDCreate();
	
	void *new_task = TaskCreate(new_uid, interval_in_sec, is_repeating, task_func, params);
	
	assert(NULL != sched);
	assert(NULL != task_func);
	
	if(PQEnqueue(sched->tasks, new_task))
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(new_task);
		return BadUID;
	}
	return new_uid;

}

void SchedRun(sched_t *sched)
{	
	task_t *tmp = NULL;
	time_t my_time = 0;
	
	assert(NULL != sched);
	sched->is_running = 1;
	
	while(sched->is_running &&  !SchedIsEmpty(sched))
	{	
		printf("enter loop\n");
		
		tmp = PQPeek(sched->tasks);
		my_time = (TaskGetTime(tmp) - time(0));
		
		printf("%ld\n", my_time);
		sleep(my_time);
		
		TaskExecute(tmp);
	
		PQDequeue(sched->tasks);
		
		if(TaskIsRepeating(tmp))
		{	
			printf("enter if\n");
			TaskCalculateNewTime(tmp);
			PQEnqueue(sched->tasks, tmp);
		}
		else
		{
			TaskDestroy(tmp);
		}
	}
}

void SchedStop(sched_t *sched)
{
	assert(NULL != sched);
	sched->is_running = 0;
}


void SchedRemoveTask(sched_t *sched, ilrd_uid_t uid)
{
	void * id = &uid;
	assert(NULL != sched);
	PQErase(sched->tasks, CompareUID, id);
	
}

void SchedDestroy(sched_t *sched)
{
	PQDestroy(sched->tasks);
	free(sched);
}

size_t SchedSize(const sched_t *sched)
{	
	assert(NULL != sched);
	return PQSize(sched->tasks);
}

int SchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	return PQIsEmpty(sched->tasks);
}

void SchedClear(sched_t *sched)
{
	assert(NULL != sched);
	PQFlush(sched->tasks);
}





































