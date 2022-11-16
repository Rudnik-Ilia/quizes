/*****************************************************
* Topic: HEAP                                                 
* Author: Rudnik Ilia                                
* Date: 18.11.2022                                  
* Reviewer: Ira                          
* Review status: reviewed                            
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <alloca.h>

#include <math.h> 
#include "heap.h"
#include "vector.h"
#include "utils.h"

#define CAPACITY 10

#define less(a, b) a < b
#define VOID sizeof(void*)
#define PARENT(i) floor((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)

struct heap
{
	vector_t *heap_vector;
	int (*cmp_func)(const void *left, const void *right);
};

/*************************************************************************************/
static void SwapVoid(void **a, void **b);
static void HeapifyDown(const heap_t *heap, int i);
static void HeapifyUp(heap_t *heap, size_t idx);
static void _remHelp(heap_t *heap, size_t index);
void* GetData(const vector_t *vector, size_t index);
/*************************************************************************************/

heap_t *HeapCreate(cmp_func_t cmp_func)
{
	heap_t *heap = NULL;
	
	heap = (heap_t*)malloc(sizeof(heap_t));
	if(NULL == heap)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	heap->heap_vector = VectorCreate(VOID, CAPACITY);
	if(NULL == heap)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(heap);
		return NULL;
	}
	heap->cmp_func = cmp_func;
	
	return heap;
}

void HeapDestroy(heap_t *heap)
{	
	assert(NULL != heap);
	
	VectorDestroy(heap->heap_vector);
	free(heap);
}

int HeapPush(heap_t *heap, const void *data)
{	
	
	assert(NULL != heap);
	assert(NULL != data);
	
	VectorPushBack(heap->heap_vector,data);

	
	HeapifyUp(heap, HeapSize(heap) - 1);
	
	/*
	i = HeapSize(heap) - 1;
	
	for (; i > 0 && heap->cmp_func(VectorGetAccessToElement(heap->heap_vector, PARENT(i)), VectorGetAccessToElement(heap->heap_vector, i)) < 0; i = PARENT(i))
	{
		SwapVoid(VectorGetAccessToElement(heap->heap_vector, i), VectorGetAccessToElement(heap->heap_vector, PARENT(i)));
	}
	*/
	return 0;
}

void *HeapRemove(heap_t *heap, is_match_t is_match, void *param)
{
	size_t i = 0;
	void *data = NULL;
	int flag = 0;

	assert(NULL != heap);
	assert(NULL != param);
	

	for(data = GetData(heap->heap_vector, i), flag = is_match(data, param); i < HeapSize(heap) - 1 && !flag; data = GetData(heap->heap_vector, ++i), flag = is_match(data, param));
	
	if(!flag)
	{
		return NULL;
	}

	data = GetData(heap->heap_vector, HeapSize(heap)-1);
	
	_remHelp(heap, i);

	return data;

}


void HeapPop(heap_t *heap)

{	/*
	if(!HeapIsEmpty(heap))
	{
		return;
	}
	*/
	assert(NULL != heap);
	
	_remHelp(heap, 0);
}

void *HeapPeek(const heap_t *heap)
{
	assert(NULL != heap);
	return (VectorGetAccessToElement(heap->heap_vector, 0));
}

size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	return VectorSize(heap->heap_vector);
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	return VectorIsEmpty(heap->heap_vector);
}
/***************************************************************************************/

static void _remHelp(heap_t *heap, size_t index)
{		
	SwapVoid(VectorGetAccessToElement(heap->heap_vector, index), VectorGetAccessToElement(heap->heap_vector, HeapSize(heap) - 1));
	VectorPopBack(heap->heap_vector);
	HeapifyDown(heap, index);
}

void PrintHeap(const heap_t *heap)
{
	size_t i = 0;
	for(i = 0; i < HeapSize(heap); ++i)
	{
		printf("%d ", *(int*)VectorGetAccessToElement(heap->heap_vector, i));
	}
	printf("\n");
}

void* GetData(const vector_t *vector, size_t index)
{
	return VectorGetAccessToElement(vector, index);
}
/*
static void SwapVoid(void *a, void *b, size_t size)
{	
	void *tmp = NULL;
	tmp = alloca(sizeof(void*));
	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);
}
*/

static void SwapVoid(void **a, void **b) 
{ 
	void *tmp = *a; 
	*a = *b; 
	*b = tmp; 
}
static void HeapifyDown(const heap_t *heap, int i)
{
	int smallest = 0;
	
	while (1) 
	{
		smallest = i;
		
		if ((size_t)LEFT(i) < HeapSize(heap) && heap->cmp_func(VectorGetAccessToElement(heap->heap_vector, LEFT(i)), VectorGetAccessToElement(heap->heap_vector, smallest)) > 0 )
		{
			smallest = LEFT(i);
		}
		if ((size_t)RIGHT(i) < HeapSize(heap) && heap->cmp_func(VectorGetAccessToElement(heap->heap_vector, RIGHT(i)), VectorGetAccessToElement(heap->heap_vector, smallest)) > 0 )
		{
			smallest = RIGHT(i);
		}
		if (smallest == i) 
		{
			break;
		} 
		else 
		{
			SwapVoid(VectorGetAccessToElement(heap->heap_vector, i), VectorGetAccessToElement(heap->heap_vector, smallest));
			i = smallest;
		}
	}
}
static void HeapifyUp(heap_t *heap, size_t idx)
{
	size_t parent = PARENT(idx);

	assert(NULL != heap);

	if (idx == 0)
	{
		return;
	}

	if (heap->cmp_func(VectorGetAccessToElement(heap->heap_vector, idx), VectorGetAccessToElement(heap->heap_vector, parent)) > 0)
	{
		SwapVoid(VectorGetAccessToElement(heap->heap_vector, idx), VectorGetAccessToElement(heap->heap_vector, parent));
	}
	else
	{
		return;
	}
	HeapifyUp(heap, parent);
}







