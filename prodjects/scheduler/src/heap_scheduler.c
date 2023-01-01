
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
#include "heap_scheduler.h"
#include "heap.h"


#include "heap_pq.h"
#include "task.h"
#include "utils.h"


struct scheduler
{
    heap_pq_t *tasks;
    int is_running;
    #ifndef NDEBUG
    ilrd_uid_t error;
    #endif
	
};


static int CompareTime(const void *tsk1, const void *tsk2)
{
	assert(NULL != tsk1);
	assert(NULL != tsk2);
	return TaskGetTime((task_t *)tsk2) - TaskGetTime((task_t *)tsk1); 
}

static int CompareUID(const void *task, const void *uid)
{	
	assert(NULL != task);	
	return UIDIsSame(TaskGetUID((task_t*)task), *(ilrd_uid_t*)uid);
}

heap_sched_t *HeapSchedCreate(void)
{
	heap_sched_t *new_sched = (heap_sched_t *)malloc(sizeof(heap_sched_t ));
	if(NULL == new_sched)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}	
	
	new_sched -> tasks = HeapPQCreate(CompareTime);
	if(NULL == new_sched-> tasks)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(new_sched);
		return NULL;
	}
	new_sched -> is_running = 0;
	
	#ifndef NDEBUG
	new_sched->error = BadUID;
	#endif
	
	return new_sched;
}


ilrd_uid_t HeapSchedAddTask(heap_sched_t *sched, time_t interval_in_sec, int is_repeating, int (*task_func)(void *params), void *params)
{	
	 
	ilrd_uid_t new_uid = UIDCreate();
	
	void *new_task = TaskCreate(new_uid, interval_in_sec, is_repeating, task_func, params);
	
	if(NULL == new_task)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return BadUID;
	}
	
	assert(NULL != sched);
	assert(NULL != task_func);
	
	if(HeapPQEnqueue(sched->tasks, new_task))
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(new_task);
		return BadUID;
	}
	
	
	return new_uid;

}

int HeapSchedRun(heap_sched_t *sched)
{	
	task_t *tmp = NULL;
	time_t mytime = 0;
	int status = 0;
	ilrd_uid_t uid= BadUID;
	
	assert(NULL != sched);
	sched->is_running = 1;
	
	while(sched->is_running && !HeapSchedIsEmpty(sched))
	{	
		tmp = HeapPQPeek(sched->tasks);
		mytime = time(NULL);
		uid = TaskGetUID(tmp);
		
		/*
		interval = TaskGetInterval(tmp);
		*/
		sleep(TaskGetTime(tmp)-mytime);
		
		
		
		if(0 != (status = TaskExecute(tmp)))
		{
			#ifndef NDEBUG
			sched->error = TaskGetUID(tmp);
			#endif
			LOGERROR("FUNCTION FAIL");
			return status;
		}
		
		
		
		if(!HeapPQIsEmpty(sched->tasks) && UIDIsSame(uid, TaskGetUID(HeapPQPeek(sched->tasks))))
		{
			HeapPQDequeue(sched->tasks);
			
			if(TaskIsRepeating(tmp))
			{	
				TaskCalculateNewTime(tmp);
				HeapPQEnqueue(sched->tasks, tmp);
				
				/*
				TaskSetInterval(tmp, 10);
				TaskSetOFFRepeat(tmp);
				*/
			}
			else
			{
				TaskDestroy(tmp);
			}
		}	
	}
	return status;
}

void HeapSchedStop(heap_sched_t *sched)
{
	assert(NULL != sched);
	sched->is_running = 0;
}


void HeapSchedRemoveTask(heap_sched_t *sched, ilrd_uid_t uid)

{
	void * id = &uid;
	assert(NULL != sched);
	TaskDestroy((task_t*)HeapPQErase(sched->tasks, CompareUID, id));	
}

void HeapSchedDestroy(heap_sched_t *sched)
{
	assert(NULL != sched);
	HeapSchedClear(sched);	
	HeapPQDestroy(sched->tasks);
	free(sched);	
}


size_t HeapSchedSize(const heap_sched_t *sched)
{	
	assert(NULL != sched);
	return HeapPQSize(sched->tasks);
}

int HeapSchedIsEmpty(const heap_sched_t *sched)
{
	assert(NULL != sched);
	return HeapPQIsEmpty(sched->tasks);
}

void HeapSchedClear(heap_sched_t *sched)
{
	assert(NULL != sched);     
	while (!HeapPQIsEmpty(sched->tasks))
	{
		task_t *task = HeapPQDequeue(sched->tasks);
		TaskDestroy(task);
	}
}





































