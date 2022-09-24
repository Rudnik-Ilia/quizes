
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
#include "scheduler.h"
#include "pqueue.h"
#include "all.h"
#include "utils.h"



struct scheduler
{
    pq_t *tasks;
    int is_running;
    
};



static int Compare(const void *data1, const void *data2)
{

return 0;
}

sched_t *SchedCreate(void)
{
	sched_t *new_sched = (sched_t*)malloc(sizeof(sched_t));
	if(NULL == new_sched)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}	
	
	new_sched -> tasks = PQCreate(Compare);

	return new_sched;
}

void SchedDestroy(sched_t *sched)
{

	free(sched);
}



