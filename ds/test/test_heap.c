
#include <stdio.h>

#include "heap.h"
#include "test.h"

#define CAPACITY 10


int Compare(const void * p1, const void * p2)
{
	return *(int*)p1 - *(int*)p2;
}

int main()
{	       /*    0    1   2   3   4   5   6   7   8   9   10   11  */
	int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 5 , 1} ;
	
	
	heap_t *heap = HeapCreate(Compare);
	
	TEST("Size: ", HeapSize(heap), 0);
	TEST("Size: ", HeapIsEmpty(heap), 0);
	
	HeapPush(heap, &arr[9]);
	HeapPush(heap, &arr[8]);
	HeapPush(heap, &arr[7]);
	HeapPush(heap, &arr[6]);
	HeapPush(heap, &arr[5]);
	HeapPush(heap, &arr[4]);
	HeapPush(heap, &arr[3]);
	HeapPush(heap, &arr[2]);
	HeapPush(heap, &arr[1]);
	HeapPush(heap, &arr[0]);
	HeapPush(heap, &arr[10]);
	HeapPush(heap, &arr[11]);
	/*
	*/
	
	TEST("Size: ", HeapSize(heap), 12);
	TEST("Size: ", HeapIsEmpty(heap), 1);
	TEST("Peek: ", *(int*)HeapPeek(heap), 1);
	
	
	PrintHeap(heap);
	HeapPop(heap);
	PrintHeap(heap);
	HeapPop(heap);
	PrintHeap(heap);
	
	HeapRemove(heap, Compare, &arr[9]);
	
	PrintHeap(heap);

	HeapDestroy(heap);
return 0;
}
