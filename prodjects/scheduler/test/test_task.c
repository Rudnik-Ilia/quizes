

#include <stdio.h>
#include <stdlib.h>

#include "ilrd_uid.h"
#include "task.h"
#include "test.h"




int Exam(void *x)
{
	return *(int*)x*2;
}




int main()
{		
	int a = 11;
	ilrd_uid_t id = UIDCreate();
	ilrd_uid_t id2 = UIDCreate();
	
	task_t *new = TaskCreate(id, 60, 0, Exam, &a);
	task_t *new2 = TaskCreate(id2, 60, 0, Exam, &a);
	
	TEST("Test for func ",TaskExecute(new), 22);
	TEST("Test for repeat ",TaskIsRepeating(new), 0);
	
	TEST("For UID the same", UIDIsSame(id, TaskGetUID(new)),0);
	
	TEST("For UID NOT the same", UIDIsSame(TaskGetUID(new2), TaskGetUID(new)),1);
	


	TaskDestroy(new2);
	TaskDestroy(new);
	PASS;
return 0;
}
