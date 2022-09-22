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
	sorted_list_iterator_t tmp;
	
	assert(NULL != pqueue);
	assert(NULL != data);
	
	tmp = SortedLLInsert(pqueue->list, data);
	
	return NULL == tmp.dll_iter ? 0 : 1;
}

void *PQDequeue(pq_t *pqueue)
{
	assert(NULL != pqueue);
	return SortedLLPopFront(pqueue->list);
}


void *PQPeek(const pq_t *pqueue)
{	
	assert(NULL != pqueue);
	return SortedLLGetData(SortedLLBegin(pqueue->list));
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
	
	SortedLLMerge(dest->list, src->list);
	return dest;
}

void PQFlush(pq_t *pqueue)
{
	sorted_list_iterator_t tmp = SortedLLBegin(pqueue -> list);
	
	assert(NULL != pqueue);
	
	for(; !SortedLLIsEqualIter(tmp, SortedLLEnd(pqueue -> list)); SortedLLRemove(tmp))
	{
		/* EMPTY BODY*/
	}
}

void *PQErase(pq_t *pqueue, int (*is_match)(const void *data, void *params), void *params)
{
	sorted_list_iterator_t tmp;
	
	void * ptr = NULL;	
		
	assert(NULL != pqueue);
	assert(NULL != is_match);
	assert(NULL != params);
	
	tmp = SortedLLFindIf(SortedLLBegin(pqueue -> list),  SortedLLEnd(pqueue -> list), is_match, params);
	
	if(SortedLLIsEqualIter(tmp, SortedLLEnd(pqueue -> list)))
	{
		return NULL;
	}
	ptr = SortedLLGetData(tmp);
	SortedLLRemove(tmp);
	
	return ptr;
}




























