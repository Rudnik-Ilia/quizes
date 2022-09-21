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
#include "pqueue.h"
#include "utils.h"
#include "dll.h"


typedef int(*priority_cmp_func)(const void *data1, const void *data2);


struct priority_queue  
{
    sorted_list_t *list;
};



pq_t *PQCreate(priority_cmp_func func_cmp)
{
	
	pq_t *pq = (pq_t*)malloc(sizeof(pq_t));
	
	if(NULL == pq)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	} 
	pq->list = SortedLLCreate(func_cmp);
	
	return pq;
}


int PQEnqueue(pq_t *pqueue, void *data)
{
	assert(NULL != pqueue);
	assert(NULL != data);
	
	SortedLLInsert(pqueue->list, data);
	
	return 0;
}

void *PQDequeue(pq_t *pqueue)
{
	assert(NULL != pqueue);
	return SortedLLPopBack(pqueue->list);
}


void *PQPeek(const pq_t *pqueue)
{	
	assert(NULL != pqueue);
	return SortedLLGetData(SortedLLPrev(SortedLLEnd(pqueue->list)));
}

void PQDestroy(pq_t *pqueue)
{
	SortedLLDestroy(pqueue->list);
	free(pqueue);
}

int PQIsEmpty(const pq_t *pqueue)
{
	assert(NULL != pqueue);
	return SortedLLIsEmpty(pqueue->list);
}
size_t PQSize(const pq_t *pqueue)
{	
	assert(NULL != pqueue);
	return SortedLLSize(pqueue->list);

}

pq_t *PQMerge(pq_t *dest, pq_t *src)

{
	assert(NULL != dest);
	assert(NULL != src);
	
	return dest->list = SortedLLMerge(dest->list, src->list);
}





























