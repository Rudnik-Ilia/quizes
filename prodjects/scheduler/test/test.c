/****************************
*Author: Viktor Cherviakov *
*Group: OL132              *
*WS: Scheduler             *
*Reviewer: Ilia            *
*Status: tbd               *
****************************/

#include <assert.h>

#include "tests.h"
#include "ilrd_uid.h"
#include "scheduler.h"


size_t test_counter = 0;
size_t remove_counter = 5;
size_t success_counter = 0;
static int timer = 0;

struct numbers
{	
	int a;
	int b;
	int c;
};

struct task_params
{
	sched_t* sched;
	ilrd_uid_t uid;
};
typedef struct numbers numbers_t;
typedef struct task_params task_params_t;

static int Timer(void *params);
static int PlusInt(void *params);
static int XoXo(void *params);
static int Stop(void *params);

void Tests();

int main()
{
	Tests();
	SHOWRESULTS;

	return 0;	
}

static int Timer(void *params)
{
	(void)params;
	printf("timer works %d\n", ++timer);
	return 0;
}

static int PlusInt(void *params)
{
	numbers_t *num = (numbers_t*)params;
	assert(NULL != params);
	printf("PlusInt: %d\n", num->a + num->b + num->c);
	++num->a;
	++num->b;
	++num->c;
	return 0;
}

static int XoXo(void *params)
{
	(void)params;
	puts("XoXoXo");
	return 0;
}

static int Stop(void *params)
{
	sched_t *sched = (sched_t*)params;
	SchedStop(sched);
	return 0;
}

static int RemoveMe(void *params)
{
	task_params_t *q = (task_params_t*)params;
	if(remove_counter == 0)
	{
		SchedRemoveTask(q->sched, q->uid);
		return 0;
	}

	printf("Remove me in %lu\n", remove_counter);
	--remove_counter;

	return 0;
}

void Tests()
{
	numbers_t num = {0,0,0};
	task_params_t q;
	void *useless = (void*)0xDEADBEEF;
	ilrd_uid_t dummy_uid = BadUID;
	
	ilrd_uid_t runner1 = BadUID;
	
	sched_t *sched = SchedCreate();
	q.sched = sched;
	q.uid = BadUID;
	TEST(1, SchedIsEmpty(sched));
	TEST(0, SchedSize(sched));
	
	SchedAddTask(sched, 1, 1, Timer, useless);
	TEST(0, SchedIsEmpty(sched));
	TEST(1, SchedSize(sched));

	q.uid = SchedAddTask(sched, 1, 1, RemoveMe, &q);
	
	SchedAddTask(sched, 2, 1, PlusInt, &num);
	TEST(3, SchedSize(sched));
	
	runner1 = SchedAddTask(sched, 4, 1, XoXo, useless);
	TEST(4, SchedSize(sched));
	
	SchedAddTask(sched, 10, 0, Stop, sched);
	TEST(5, SchedSize(sched));
	
	SchedRun(sched);
	
	puts("remove XoXo and re-run scheduler");
	SchedRemoveTask(sched, runner1);
	printf("%ld\n", SchedSize(sched));
	TEST(2, SchedSize(sched));
	
	/* Trying to remove not valid task. Assert on debug or OK on release */
	/*
	SchedRemoveTask(sched, runner1);
	SchedRemoveTask(sched, dummy_uid);
	*/
	SchedAddTask(sched, 5, 0, Stop, sched);

	SchedRun(sched);

	SchedClear(sched);
	TEST(1, SchedIsEmpty(sched));
	TEST(0, SchedSize(sched));
	
	/* check destroy func */
	SchedAddTask(sched, 2, 1, PlusInt, &num);
	TEST(0, SchedIsEmpty(sched));
	TEST(1, SchedSize(sched));
	
	
	
	SchedDestroy(sched);
}

