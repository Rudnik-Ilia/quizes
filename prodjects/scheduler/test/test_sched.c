
#include <stdio.h>
#include <unistd.h> /* getpid */
#include <stdlib.h>

#include "scheduler.h"
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
	SchedStop(x);
	return 0;
}


int main()
{	
/*
	ilrd_uid_t first;
	ilrd_uid_t second;
	ilrd_uid_t thrid;
	ilrd_uid_t fail;
	ilrd_uid_t stop;
*/
	
	
	int a = 11;
	sched_t *new_sched  = SchedCreate();
	
	printf("ISempty: %d\n",SchedIsEmpty(new_sched));
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	SchedAddTask(new_sched, 5, 0, Exam, &a);
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	SchedAddTask(new_sched, 3, 1, Exam2, &a);
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	SchedAddTask(new_sched, 6, 0, Exam3, &a);
	
	printf("ISempty: %d\n",SchedIsEmpty(new_sched));
	
	SchedAddTask(new_sched, 15, 0, Stop, new_sched);
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	
	
	
	
	SchedRun(new_sched);
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	
	/*
	SchedAddTask(new_sched, 4, 0, ExamFail, &a);
	printf("Size after remove: %ld\n",SchedSize(new_sched));
	SchedRemoveTask(new_sched, first);
	printf("%d\n", UIDIsSame(second, first));
	printf("%d\n", UIDIsSame(first, first));
	*/
	SchedDestroy(new_sched);
	
return 0;
}
