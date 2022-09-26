
#include <stdio.h>
#include <unistd.h> /* getpid */
#include <time.h>
#include <stdlib.h>
#include "scheduler.h"
#include "ilrd_uid.h"


int Exam(void *x)
{	
	printf("1111");
	return *(int*)x*2;
}

int Exam2(void *x)
{
	printf("2222");
	return *(int*)x*100;
}


int main()
{	
	ilrd_uid_t first;
	ilrd_uid_t second;
	
	int a = 11;
	sched_t *new_sched  = SchedCreate();
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	first = SchedAddTask(new_sched, 40, 1, Exam, &a);
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	second = SchedAddTask(new_sched, 40, 1, Exam2, &a);
	
	printf("Size: %ld\n",SchedSize(new_sched));
	
	
	SchedRemoveTask(new_sched, first);
	printf("Size after remove: %ld\n",SchedSize(new_sched));
	
	/*
	printf("%d\n", UIDIsSame(second, first));
	printf("%d\n", UIDIsSame(first, first));
	*/
	SchedDestroy(new_sched);
	
return 0;
}
