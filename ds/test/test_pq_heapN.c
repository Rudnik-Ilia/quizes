#include <stdio.h>  /* printf */
#include <assert.h>

#include "pq_heap.h"
#include "test.h"

#define LESS -1
#define GREATER 1
#define EQUAL 0

int ActionFunction(const void *data_one, void *params);
int CompareFunc(const void *data_one, const void *data_two);
void TestFunction();


int main()
{
	TestFunction();
	PASS;
	return 0;	
}

void TestFunction()
{
	int data_one = 20;
	int data_two = 10;
	int data_three = 30;
	int data_four = 20;
	int data_five = 15;
	
	
	int x = 2;

	heap_pq_t *pq = HeapPQCreate(CompareFunc);
	
	HeapPQEnqueue(pq, &data_one);
	HeapPQEnqueue(pq, &data_two);
	HeapPQEnqueue(pq, &data_three);
	HeapPQEnqueue(pq, &data_four);
	HeapPQEnqueue(pq, &data_five);
	

	TEST("Test size", HeapPQSize(pq), 5);
	TEST("Test peek", *(int *)HeapPQPeek(pq), data_three);
	
	HeapPQErase(pq, &CompareFunc, &x);
	TEST("Test size", HeapPQSize(pq), 4);
	
	HeapPQDequeue(pq);
	TEST("Test size", HeapPQSize(pq), 3);

	HeapPQFlush(pq);
	TEST("Test size", HeapPQSize(pq), 0);
	HeapPQDestroy(pq);	
}

/*************** Helper function *************************/
int CompareFunc(const void *data_one, const void *data_two)
{	
	assert(NULL != data_one);
	assert(NULL != data_two);
	
	if(*(int*)data_one < *(int*)data_two)
	{
		return GREATER;
	}
	
	if(*(int*)data_one > *(int*)data_two)
	{
		return LESS;
	}
	
	return EQUAL;
}

int ActionFunction(const void *data_one, void *params)
{
	assert(NULL != data_one);
	assert(NULL != params);
	return (*(int*)data_one % (*(int*)params)) ? 1 : 0;
	
}
