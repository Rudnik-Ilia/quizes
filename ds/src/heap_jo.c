/**
* Title: Heap
* Author: Johnatan S
* Date: November 15th
* Reviewer: Alena
* Review status: TBR
**/
#include <stdlib.h>
#include <assert.h>

#include "vector.h"
#include "heap.h"
#include "utils.h"

#define PARENT_INDEX(index) (((index) -1 ) / 2)
#define CHILD_INDEX(index, side) ((2 * (index)) + side)

#define PARENT(heap, index) (VectorGetAccessToElement((heap)->heap_vector, PARENT_INDEX(index)))
#define CURRENT(heap, index) (VectorGetAccessToElement((heap)->heap_vector, (index)))
#define CHILD(heap, index, side) (VectorGetAccessToElement((heap)->heap_vector, CHILD_INDEX(index, side)))

#define LESS_THAN(heap, data1, data2) (((heap)->cmp_func(GET_DATA((data1)), GET_DATA((data2)))) < 0)
#define GREATER_THAN(heap, data1, data2) (((heap)->cmp_func(GET_DATA((data1)), GET_DATA((data2)))) > 0)

#define GET_DATA(a) ((void *)*(size_t *)(a))

#define VECTOR_DEFAULT_CAPACITY 100
#define WORD_SIZE sizeof(size_t)

#define LEFT 1
#define RIGHT 2

struct heap
{
    vector_t *heap_vector;
    int (*cmp_func)(const void *left, const void *right);
};

static void HeapifyUp(heap_t *heap, size_t index); 
static void HeapifyDown(heap_t *heap, size_t index);

static void SwapVectorElements(void **a, void **b);
static void HeapRemoveAux(heap_t *heap, size_t index);

heap_t *HeapCreate(cmp_func_t cmp_func)
{
    heap_t *heap = NULL;
    vector_t *vct = NULL;

    assert(NULL != cmp_func);

    heap = (heap_t *)malloc(sizeof(heap_t));
    if(NULL == heap)
    {
       
        return NULL;
    }

    vct = VectorCreate(WORD_SIZE, VECTOR_DEFAULT_CAPACITY);
    if(NULL == vct)
    {
      
        free(heap);
        return NULL;
    }

    heap->cmp_func = cmp_func;
    heap->heap_vector = vct;

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

    if(!VectorPushBack(heap->heap_vector, &data))
    {
        return 1;
    }

    HeapifyUp(heap, HeapSize(heap) - 1);

    return 0;
}

void HeapPop(heap_t *heap)
{
    assert(NULL != heap);
    HeapRemoveAux(heap, 0);
}

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return GET_DATA(CURRENT(heap, 0));
}

static void HeapRemoveAux(heap_t *heap, size_t index)
{
    SwapVectorElements(CURRENT(heap, index), CURRENT(heap, HeapSize(heap) - 1));
    VectorPopBack(heap->heap_vector);
    HeapifyUp(heap, index);
    HeapifyDown(heap, index);
}

void *HeapRemove(heap_t *heap, is_match_t is_match, void *param)
{
    size_t i = 0;
    int isMatch = 0;
    void *rem_data = NULL;

    assert(NULL != heap);
    assert(NULL != is_match);
    assert(NULL != param);

    for(rem_data = GET_DATA(CURRENT(heap, i)), isMatch = is_match(rem_data, param);
        i < HeapSize(heap) - 1 && !isMatch; 
        rem_data = GET_DATA(CURRENT(heap, ++i)), isMatch = is_match(rem_data, param));
    
    if(!isMatch)
    {
        return NULL;
    }

    HeapRemoveAux(heap, i);

    return rem_data;
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

static void HeapifyUp(heap_t *heap, size_t index) 
{
    size_t i  = index;
    void *parent = NULL;
    void *current = NULL;

    if( i <= 0)
    {
        return;
    }

    parent = PARENT(heap, i);
    current = CURRENT(heap, i);

    if(LESS_THAN(heap, parent, current))
    {
        SwapVectorElements(parent, current);
        HeapifyUp(heap, PARENT_INDEX(i));
    }

    return;

}

static void HeapifyDown(heap_t *heap, size_t index)
{
    size_t i = index;
    int side = LEFT;
    
    void *current = NULL;
    void *child= NULL;

    if(CHILD_INDEX(i, LEFT) >= HeapSize(heap))
    {
        return;
    }

    current = CURRENT(heap, i);
    child = CHILD(heap, i, LEFT);

    if(CHILD_INDEX(i, RIGHT) < HeapSize(heap) && 
        GREATER_THAN(heap, CHILD(heap, i, RIGHT), child))
    {
        side = RIGHT;
        child = CHILD(heap, i, RIGHT);
    }
    
    if(GREATER_THAN(heap, child, current))
    {
        SwapVectorElements(current, child);
        HeapifyDown(heap, CHILD_INDEX(i, side));
    }

    return;
}

static void SwapVectorElements(void **a, void **b)
{
    void *tmp = *a;
    *a = *b;
    *b = tmp;    
}

/*static void HeapPrint(heap_t *heap)
{
    size_t i = 0;

    for(; i < HeapSize(heap); ++i)
    {
        printf("%d ", *(int *)GET_DATA(CURRENT(heap, i)));
    }

    puts("\n--------------------------------");
}*/
