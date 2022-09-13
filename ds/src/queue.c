
/**********************
* Title : Worksheet Q
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/

#include <assert.h>
#include <stdlib.h>
#include "utils.h"
#include "queue.h"
#include "SLL.h"


struct queue{
	sll_t* p_q;
};

queue_t *QueueCreate()
{
	queue_t *queue = (queue_t*)malloc(sizeof(queue));
	if(NULL == queue)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	queue->p_q = SllCreate();
	if(NULL == queue->p_q)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	return queue;
}

int QueueEnqueue(queue_t *queue, void *data)
{
	iterator_t iter = SllInsert(SllEnd(queue -> p_q), data);
	return (NULL == iter);	
}

void QueueDequeue(queue_t *queue)
{	
	assert(queue);
	SllRemove(SllBegin(queue->p_q));
}

size_t QueueSize(const queue_t *queue)
{	
	assert(queue);
	return SllCount(queue -> p_q);
}

void *QueuePeek(const queue_t *queue)
{	
	assert(queue);
	return SllGetData(SllBegin(queue->p_q));
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	return SllIsEmpty(queue->p_q);
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);
	SllAppend(dest->p_q, src->p_q);  
	return dest;
}

void QueueDestroy(queue_t *queue)
{	
	assert(queue);
	SllDestroy(queue->p_q);
	free(queue);
}



