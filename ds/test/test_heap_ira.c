#include <assert.h>

#include "../include/heap.h"
#include "../include/tests.h"

#define SIZE 10

static int CmpFunc(const void *data1, const void *data2);
static int IsMatchInt(const void *data, const void *param);
void Test();

int main()
{
    Test();
    PASS;
    return 0;    
}

void Test()
{
    heap_t *heap = HeapCreate(CmpFunc);
    int arr[SIZE] = {2, 546, 11, 85, 12, 5, 98, 77, 3};
    size_t i = 0;

    TEST("Test HeapCreate()", NULL != heap, 1);
    TEST("Test HeapSize()", HeapSize(heap), 0);
    TEST("Test HeapIsEmpty()", HeapIsEmpty(heap), 1);

    for(; i < SIZE; ++i)
    {        
        TEST("Test HeapPush()", HeapPush(heap, &arr[i]), 0);
        TEST("Test HeapSize()", HeapSize(heap), i + 1);
    }
    PrintHeap(heap);
    TEST("Test HeapPeek()", *(int *)(HeapPeek(heap)), arr[1]);

    for(i = 0; i < SIZE; ++i)
    {        
        TEST("Test HeapRemove()", *(int *)(HeapRemove(heap, IsMatchInt, &arr[i])), arr[i]);
        TEST("Test HeapPop()", HeapSize(heap), SIZE - 1 - i);
    }

    for(i = 0; i < SIZE; ++i)
    {        
        TEST("Test HeapPush()", HeapPush(heap, &arr[i]), 0);
        TEST("Test HeapSize()", HeapSize(heap), i + 1);
    }

    for(i = 0; i < SIZE; ++i)
    {        
        HeapPop(heap);
        TEST("Test HeapPop()", HeapSize(heap), SIZE - 1 - i);
    }
    HeapDestroy(heap);
}

static int CmpFunc(const void *data1, const void *data2)
{
    return *(int *)data1 - *(int *)data2; 
}

static int IsMatchInt(const void *data, const void *param)
{
    return *(int *)data == *(int *)param;
}

