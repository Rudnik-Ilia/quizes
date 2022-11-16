/**********************
* Title : Worksheet PQ
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/


#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "srtll.h"
#include "heap_pq.h"
#include "utils.h"
#include "heap.h"


typedef int(*priority_cmp_func)(const void *data1, const void *data2);


struct priority_queue
{
	heap_t *heap;
};



heap_pq_t *HeapPQCreate(int(*priority_cmp_func)(const void *data1, const void *data2))
{
	
	heap_pq_t *pq = (heap_pq_t*)malloc(sizeof(heap_pq_t));
	
	if(NULL == pq)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	} 
	pq->heap = HeapCreate(priority_cmp_func);
	
	if(NULL == pq->heap)
	{
		free(pq);
		return NULL;
	}
	return pq;
}

int HeapPQEnqueue(heap_pq_t *pqueue, void *data)
{
	
	assert(NULL != pqueue);
	assert(NULL != data);
	
	return HeapPush(pqueue->heap, data);
}

void *HeapPQDequeue(heap_pq_t *pqueue)
{	
	void *data = NULL;
	
	assert(NULL != pqueue);
	
	data = HeapPeek(pqueue->heap);
	HeapPop(pqueue->heap);
	
	return data;
}


void *HeapPQPeek(const heap_pq_t *pqueue)
{	
	assert(NULL != pqueue);
	return HeapPeek(pqueue->heap);
}

void HeapPQDestroy(heap_pq_t *pqueue)
{
	HeapDestroy(pqueue->heap);
	free(pqueue);
}

int HeapPQIsEmpty(const heap_pq_t *pqueue)
{
	assert(NULL != pqueue);
	return HeapIsEmpty(pqueue->heap);
}

size_t HeapPQSize(const heap_pq_t *pqueue)
{	
	assert(NULL != pqueue);
	return HeapSize(pqueue->heap);

}

void HeapPQFlush(heap_pq_t *pqueue)
{
	
	assert(NULL != pqueue);

	while(HeapIsEmpty(pqueue->heap))
	{
		HeapPop(pqueue->heap);
	}

}

void *HeapPQErase(heap_pq_t *pqueue, int (*is_match)(const void *data, const void *params), void *params)
{		
	assert(NULL != pqueue);
	assert(NULL != is_match);
	assert(NULL != params);
	
	return HeapRemove(pqueue->heap, is_match, params);
}



