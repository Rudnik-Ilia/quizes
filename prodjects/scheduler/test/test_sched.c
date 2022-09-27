
#include <stdio.h>
#include <unistd.h> /* getpid */
#include <stdlib.h>

#include "scheduler.h"
#include "ilrd_uid.h"


int Exam(void *x)
{	
	printf("first\n");
	return *(int*)x*2;
}

int Exam2(void *x)
{
	printf("second\n");
	return *(int*)x*100;
}

int Exam3(void *x)
{
	printf("thrid\n");
	return *(int*)x*100;
}


int main()
{	
	ilrd_uid_t first;
	ilrd_uid_t second;
	ilrd_uid_t thrid;
	
	
	int a = 11;
	sched_t *new_sched  = SchedCreate();
	printf("ISempty: %d\n",SchedIsEmpty(new_sched));
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	first = SchedAddTask(new_sched, 1, 7, Exam, &a);
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	second = SchedAddTask(new_sched, 0, 5, Exam2, &a);
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	thrid = SchedAddTask(new_sched, 0, 10, Exam3, &a);
	
	printf("ISempty: %d\n",SchedIsEmpty(new_sched));
	
	
	SchedRun(new_sched);
	/*
	printf("Size after remove: %ld\n",SchedSize(new_sched));
	SchedRemoveTask(new_sched, first);
	printf("%d\n", UIDIsSame(second, first));
	printf("%d\n", UIDIsSame(first, first));
	*/
	SchedDestroy(new_sched);
	
return 0;
}
