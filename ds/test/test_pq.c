
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include "utils.h"
#include "test.h"
#include "pqueue.h"


static int Compare();
static int Match();
void TestMerge();
void Test();

int main()
{
	Test();
	TestMerge();
	PASS;

return 0;
}

/**********HELP**************/
static int Compare(const void *data1, const void *data2)
{	
	return *(int*)data2 - *(int*)data1;
}

static int Match(const void *data, void *params)
{
	(void)params;
	
	assert(NULL != data);
	assert(NULL != params);
	
	return *(int*)data < 0 ? 1: 0;
}

void TestMerge()
{
	int arr[] = {1,3,5};
	int arr2[] = {2,4,6};

	
	pq_t *pq = PQCreate(Compare);
	pq_t *pq2 = PQCreate(Compare);
	
	PQEnqueue(pq, &arr[0]);
	PQEnqueue(pq, &arr[1]);
	PQEnqueue(pq, &arr[2]);
	
	PQEnqueue(pq2, &arr2[0]);
	PQEnqueue(pq2, &arr2[1]);
	PQEnqueue(pq2, &arr2[2]);

	PQMerge(pq, pq2);

	TEST("Final length", PQSize(pq),6);
	TEST("Final length", PQSize(pq2),0);
	
	
	PQDestroy(pq);
	PQDestroy(pq2);
}

void Test()
{
	pq_t *pq = PQCreate(Compare);
	int arr[] = {10, 20, 30, 55};
	int n = -7;
	TEST("IsEmpty after creater", PQIsEmpty(pq), 1);
	TEST("Size after creater", PQSize(pq), 0);
	
	PQEnqueue(pq, &arr[0]);
	PQEnqueue(pq, &arr[1]);
	
	TEST("Size after insert", PQSize(pq), 2);
	
	PQDequeue(pq);
	
	TEST("Size after insert", PQSize(pq), 1);
	
	PQEnqueue(pq, &arr[2]);
	PQEnqueue(pq, &arr[3]);
	
	PQEnqueue(pq, &n);
	TEST("Size after insert", PQSize(pq), 4);
	
	TEST("PEEK", *(int*)PQPeek(pq), 55);

	TEST("Erase",*(int*)PQErase(pq, &Match, &arr[0]), -7);
	
	TEST("Size after insert", PQSize(pq), 3);
	
	PQFlush(pq);
	TEST("Size after creater", PQSize(pq), 0);
	
	PQDestroy(pq);
}


