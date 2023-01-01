
#include <stdio.h>
#include <unistd.h> /* getpid */
#include <stdlib.h>

#include "heap_scheduler.h"
#include "ilrd_uid.h"


int Exam(void *x)
{	
	printf("first\n");
	*(int*)x = *(int*)x*2;
	return 0;
}

int Exam2(void *x)
{
	printf("second\n");
	*(int*)x = *(int*)x*100;
	return 0;
}

int Exam3(void *x)
{
	printf("thrid\n");
	*(int*)x = *(int*)x*100;
	return 0;
}
int ExamFail(void *x)
{
	(void)x;
	return -1;
}

int Stop(void *x)
{
	printf("stop\n");
	HeapSchedStop(x);
	return 0;
}


int main()
{	
/*
*/
	ilrd_uid_t first;
	ilrd_uid_t second;
	ilrd_uid_t thrid;
	ilrd_uid_t fail;
	ilrd_uid_t stop;
	
	
	int a = 11;
	heap_sched_t *new_sched  = HeapSchedCreate();
	
	printf("ISempty: %d\n",HeapSchedIsEmpty(new_sched));
	
	printf("Size: %ld\n",HeapSchedSize(new_sched));
	
	HeapSchedAddTask(new_sched, 5, 0, Exam, &a);
	
	printf("Size: %ld\n",HeapSchedSize(new_sched));
	
	HeapSchedAddTask(new_sched, 3, 1, Exam2, &a);
	
	printf("Size: %ld\n",HeapSchedSize(new_sched));
	
	HeapSchedAddTask(new_sched, 6, 0, Exam3, &a);
	
	printf("ISempty: %d\n",HeapSchedIsEmpty(new_sched));
	
	HeapSchedAddTask(new_sched, 15, 0, Stop, new_sched);
	
	printf("Size: %ld\n",HeapSchedSize(new_sched));
	
	printf("!!!!!!!!!!!!!!!!!!");
	
	HeapSchedRun(new_sched);
	
	printf("Size: %ld\n",HeapSchedSize(new_sched));
	
	
	/*
	SchedAddTask(new_sched, 4, 0, ExamFail, &a);
	printf("Size after remove: %ld\n",SchedSize(new_sched));
	SchedRemoveTask(new_sched, first);
	printf("%d\n", UIDIsSame(second, first));
	printf("%d\n", UIDIsSame(first, first));
	*/
	HeapSchedDestroy(new_sched);
	
return 0;
}
