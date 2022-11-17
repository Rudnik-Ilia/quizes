/**
 * @name    Heap ADT
 * @file    Source
 * @author  Yanai Klugman
 * @remarks Ilia
 * @date    16/11/2022
 * @todo    Dev
 * @include ../tools
 */

#include <stdlib.h> /* malloc, free */
#include <math.h>   /* floor */
#include <assert.h> /* Debugging */

#include "heap.h"   /* Heap API */
#include "vector.h" /* Vector API */
#include "utils_yan.h"  /* Utility Macros*/

/*--------------------------| TYPEDEFS & STRUCTS |---------------------------*/

struct heap
{
    vector_t *heap_vector;
    cmp_func_t cmp_func;
} /* heap_t */;

typedef enum child_e
{
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
} child_t;

/*-------------------------------| MACROS |----------------------------------*/

#define CHILD_INDEX(i, pos) ((2 * (i)) + pos)
#define PARENT_INDEX(i) floor(((i) - 1) / 2)

#define VECTOR_GET(vector, i) VectorGetAccessToElement(vector, i)

#define CHILD(heap, i, pos) \
    (VECTOR_GET((heap)->heap_vector, CHILD_INDEX(i, pos)))
#define PARENT(heap, i) \
    (VECTOR_GET((heap)->heap_vector, PARENT_INDEX(i)))
#define CURRENT(heap, i) \
    (VECTOR_GET((heap)->heap_vector, (i)))

#define GET_VOID_DATA(ptr) ((void *)*(size_t *)(ptr))

#define IS_GREATER(heap, data1, data2) \
    (((heap)->cmp_func(GET_VOID_DATA((data1)), GET_VOID_DATA((data2)))) > 0)
#define IS_LESSOREQ(heap, data1, data2) \
    (((heap)->cmp_func(GET_VOID_DATA((data1)), GET_VOID_DATA((data2)))) <= 0)

#define HEAP_VECTOR_CAPACITY 100

/*-------------------------| FORWARD DECLARATIONS |--------------------------*/

static void HeapifyUp(heap_t *heap, size_t index);
static void HeapifyDown(heap_t *heap, size_t index);
/* static void HeapPrint(heap_t *heap); */

static void VectorSwap(void **a, void **b);
static void __HeapRemove(heap_t *heap, size_t index);

/*-----------------------------| API FUNCTIONS |-----------------------------*/

heap_t *HeapCreate(cmp_func_t cmp_func)
{
    heap_t *heap = NULL;

    assert(NULL != cmp_func);

    heap = (heap_t *)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        LOGERROR("HeapCreate -| Malloc fail");
        return NULL;
    }

    heap->heap_vector = VectorCreate(WORDSIZE, HEAP_VECTOR_CAPACITY);
    if (NULL == heap->heap_vector)
    {
        LOGERROR("HeapCreate -> VectorCreate -| Malloc fail");
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
 
    if (!VectorPushBack(heap->heap_vector, &data))
    {
        return FAILURE;
    }

    HeapifyUp(heap, HeapSize(heap) - 1);
    /* HeapPrint(heap); */

    return SUCCESS;
}

void HeapPop(heap_t *heap)
{
    assert(NULL != heap);
    __HeapRemove(heap, 0);
}

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);
    return GET_VOID_DATA(CURRENT(heap, 0));
}

void *HeapRemove(heap_t *heap, is_match_t is_match, void *param)
{
    void *data_to_remove = NULL;
    size_t i = 0;
    assert(NULL != heap);
    assert(NULL != is_match);

    for (data_to_remove = GET_VOID_DATA(CURRENT(heap, i));
         i < HeapSize(heap) && !is_match(data_to_remove, param);
         data_to_remove = GET_VOID_DATA(CURRENT(heap, ++i)))
         ;
    
    if (i >= HeapSize(heap))
    {
        return NULL;
    }
  
    __HeapRemove(heap, i);

    return data_to_remove;
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

/*---------------------------| STATIC FUNCTIONS |----------------------------*/

static void HeapifyUp(heap_t *heap, size_t index)
{
    void *parent = NULL;
    void *current = NULL;

    if (index <= 0)
    {
        return;
    }

    parent = PARENT(heap, index);
    current = CURRENT(heap, index);

    if (IS_LESSOREQ(heap, parent, current))
    {
        VectorSwap(parent, current);
        HeapifyUp(heap, PARENT_INDEX(index));
    }

    return;
}

static void HeapifyDown(heap_t *heap, size_t index)
{
    child_t pos = LEFT;

    void *current = NULL;
    void *child = NULL;

    assert(NULL != heap);

    if (CHILD_INDEX(index, LEFT) >= HeapSize(heap))
    {
        return;
    }

    current = CURRENT(heap, index);
    child = CHILD(heap, index, LEFT);

    if (CHILD_INDEX(index, RIGHT) < HeapSize(heap) AND
        IS_GREATER(heap, CHILD(heap, index, RIGHT), child))
    {
        pos = RIGHT;
        child = CHILD(heap, index, RIGHT);
    }

    if (IS_GREATER(heap, child, current))
    {
        VectorSwap(current, child);
        HeapifyDown(heap, CHILD_INDEX(index, pos));
    }

    return;
}

/*
static void HeapPrint(heap_t *heap)
{
    size_t i = 0;
    puts("\n--------------------------------");
    for(; i < HeapSize(heap); ++i)
    {
        printf("%d ", *(int *)GET_VOID_DATA(CURRENT(heap, i)));
    }
}
*/

static void VectorSwap(void **a, void **b)
{
    void *tmp = *a;
    *a = *b;
    *b = tmp;    
}

static void __HeapRemove(heap_t *heap, size_t index)
{
    VectorSwap(CURRENT(heap, index), CURRENT(heap, HeapSize(heap)-1));
    VectorPopBack(heap->heap_vector);
    HeapifyDown(heap, index);
    /*HeapPrint(heap);*/
}
void PrintHeap(const heap_t *heap)
{
	size_t i = 0;
	for(i = 0; i < HeapSize(heap); ++i)
	{
		printf("%d ", *(int*)(VectorGetAccessToElement(heap->heap_vector, i)));
	}
	printf("\n");
}
/*-------------------------------| END OF FILE |-----------------------------*/
