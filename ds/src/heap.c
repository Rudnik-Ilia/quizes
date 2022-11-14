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


#include "heap.h"
#include "vector.h"
#include "utils.h"

#define CAPACITY 10


struct heap
{
	vector_t *heap_vector;
	int (*cmp_func)(const void *left, const void *right);
};
/*************************************************************************************/


/*************************************************************************************/

heap_t *HeapCreate(cmp_func_t cmp_func, size_t element_size)
{
	heap_t *heap = NULL;
	
	heap = (heap_t*)malloc(sizeof(heap_t));
	if(NULL == heap)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	heap->heap_vector = VectorCreate(element_size, CAPACITY);
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
	VectorDestroy(heap->heap_vector);
	free(heap);
}

int HeapPush(heap_t *heap, const void *data)
{
	


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








