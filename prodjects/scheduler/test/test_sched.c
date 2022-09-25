
#include <stdio.h>
#include <unistd.h> /* getpid */
#include <time.h>
#include <stdlib.h>
#include "scheduler.h"
#include "ilrd_uid.h"


int Exam(void *x)
{
	return *(int*)x*2;
}

int Exam2(void *x)
{
	return *(int*)x*100;
}


int main()
{
	int a = 11;
	sched_t *new_sched  = SchedCreate();
	
	printf("%ld\n",SchedSize(new_sched));
	
	SchedAddTask(new_sched, 40, 1, Exam, &a);
	
	printf("%ld\n",SchedSize(new_sched));
	
	SchedAddTask(new_sched, 40, 1, Exam2, &a);
	
	printf("%ld\n",SchedSize(new_sched));
	
	SchedDestroy(new_sched);
	
return 0;
}
