
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include "utils.h"
#include "test.h"
#include "pq_heap.h"
#include "heap.h"


static int Compare();
static int Match();
void Test();

int main()
{
	Test();
	
	PASS;

return 0;
}

/**********HELP**************/
static int Compare(const void *data1, const void *data2)
{	
	return *(int*)data2 - *(int*)data1;
}

static int Match(const void *data, const void *params)
{
	(void)params;
	
	assert(NULL != data);
	assert(NULL != params);
	
	return *(int*)data < 0 ? 1: 0;
}

void Test()
{
	heap_pq_t *pq = HeapPQCreate(Compare);
	int arr[] = {10, 20, 30, 55};
	int n = -7;
	TEST("IsEmpty after creater", HeapPQIsEmpty(pq), 1);
	TEST("Size after creater", HeapPQSize(pq), 0);
	
	HeapPQEnqueue(pq, &arr[0]);
	HeapPQEnqueue(pq, &arr[1]);
	
	TEST("Size after insert", HeapPQSize(pq), 2);
	
	HeapPQDequeue(pq);
	
	TEST("Size after insert", HeapPQSize(pq), 1);
	
	HeapPQEnqueue(pq, &arr[2]);
	HeapPQEnqueue(pq, &arr[3]);
	
	HeapPQEnqueue(pq, &n);
	TEST("Size after insert", HeapPQSize(pq), 4);
	
	TEST("PEEK", *(int*)HeapPQPeek(pq), 55);

	TEST("Erase",*(int*)HeapPQErase(pq, Match, &arr[0]), -7);
	
	TEST("Size after insert", HeapPQSize(pq), 3);
	
	HeapPQFlush(pq);
	TEST("Size after creater", HeapPQSize(pq), 0);
	
	HeapPQDestroy(pq);
}


