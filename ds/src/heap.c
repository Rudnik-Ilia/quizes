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

#include "heap.h"
#include "vector.h"
#include "utils.h"

#define CAPACITY 10

#define less(a, b) a < b
#define VOID sizeof(void*)


struct heap
{
	vector_t *heap_vector;
	int (*cmp_func)(const void *left, const void *right);
};

/*************************************************************************************/
static void SwapVoid(void *a, void *b, size_t size);
static int Parent(int i);
static size_t  Left(int i);
static size_t  Right(int i);
static void Heapify(const heap_t *heap, int i);
static void RemHelp(heap_t *heap, size_t index);
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
	size_t i = 0;
	
	assert(NULL != heap);
	assert(NULL != data);
	
	VectorPushBack(heap->heap_vector,data);
	i = HeapSize(heap) - 1;
	
	for (; i > 0 && heap->cmp_func(VectorGetAccessToElement(heap->heap_vector, Parent(i)), VectorGetAccessToElement(heap->heap_vector, i)) > 0; i = Parent(i))
	{
		SwapVoid(VectorGetAccessToElement(heap->heap_vector, i), VectorGetAccessToElement(heap->heap_vector, Parent(i)), VOID);
	}
	
	return 0;
}

static void RemHelp(heap_t *heap, size_t index)
{
	SwapVoid(VectorGetAccessToElement(heap->heap_vector, index), VectorGetAccessToElement(heap->heap_vector, HeapSize(heap) - 1), VOID);
	VectorPopBack(heap->heap_vector);
	Heapify(heap, index);
}


void *HeapRemove(heap_t *heap, is_match_t is_match, void *param)
{
	size_t i = 0;
	void *data = NULL;
	
	
	assert(NULL != heap);
	assert(NULL != param);
	
	if(i == HeapSize(heap))
	{
		return NULL;
	}
	
	
	data = VectorGetAccessToElement(heap->heap_vector, i);
	
	while(i < HeapSize(heap) - 1 && !is_match(data, param))
	{
		
		data = VectorGetAccessToElement(heap->heap_vector, ++i);
		
	}
	
	
	/*
	for(data = VectorGetAccessToElement(heap->heap_vector, i), flag = is_match(data, param); i < HeapSize(heap) - 1 && !flag; data = VectorGetAccessToElement(heap->heap_vector, ++i), is_match(data, param));
	*/
	
	RemHelp(heap, i);	
	return data;
}


void HeapPop(heap_t *heap)
{	
	if(!HeapIsEmpty(heap))
	{
		return;
	}
	assert(NULL != heap);
	SwapVoid(VectorGetAccessToElement(heap->heap_vector, 0), VectorGetAccessToElement(heap->heap_vector, HeapSize(heap) - 1 ), VOID);
	VectorPopBack(heap->heap_vector);
	Heapify(heap, 0);
}

void *HeapPeek(const heap_t *heap)
{
	assert(NULL != heap);
	return VectorGetAccessToElement(heap->heap_vector, 0);
}

size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	return VectorSize(heap->heap_vector);
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	return !VectorIsEmpty(heap->heap_vector);
}
/***************************************************************************************/

void PrintHeap(const heap_t *heap)
{
	size_t i = 0;
	for(i = 0; i < HeapSize(heap); ++i)
	{
		printf("%d ", *(int*)VectorGetAccessToElement(heap->heap_vector, i));
	}
	printf("\n");
}

static void SwapVoid(void *a, void *b, size_t size)
{	
	void *tmp = NULL;
	tmp = alloca(sizeof(void*));
	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);
}

static void Heapify(const heap_t *heap, int i)
{
	int smallest = 0;
	
	while (1) 
	{
		smallest = i;
		
		if (Left(i) < HeapSize(heap) && *(int*)(VectorGetAccessToElement(heap->heap_vector, Left(i))) < *(int*)(VectorGetAccessToElement(heap->heap_vector, smallest)))
		{
			smallest = Left(i);
		}
		if (Right(i) < HeapSize(heap) && *(int*)(VectorGetAccessToElement(heap->heap_vector, Right(i))) < *(int*)(VectorGetAccessToElement(heap->heap_vector, smallest)))
		{
			smallest = Right(i);
		}
		if (smallest == i) 
		{
			break;
		} 
		else 
		{
			SwapVoid(VectorGetAccessToElement(heap->heap_vector, i), VectorGetAccessToElement(heap->heap_vector, smallest), VOID);
			i = smallest;
		}
	}
}

static int Parent(int i)
{
	return (i - 1) / 2;
}

static size_t Left(int i)
{
	return 2 * i + 1;
}

static size_t Right(int i)
{
	return 2 * i + 2;
}





