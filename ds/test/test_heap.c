
#include <stdio.h>

#include "heap.h"
#include "test.h"

#define CAPACITY 10


int Compare(const void * p1, const void * p2)
{
	return *(int*)p1 - *(int*)p2;
}
int Match(const void *data, const void *param)
{
	return *(int *)data == *(int *)param;
}
void RemoveValue();
void Remove();
void GenPop();

int main()
{	
	RemoveValue();
	Remove();
	GenPop();
	/*
	*/
PASS;
return 0;
}

void RemoveValue()
{   
               /*    0   1   2   3   4   5   6   7   8   9   10   11  */
	int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 5 , 1};
	void *ptr = NULL;
	
	heap_t *heap = HeapCreate(Compare);
	
	TEST("Size: ", HeapSize(heap), 0);
	
	TEST("Size: ", HeapIsEmpty(heap), 1);

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
	
	PrintHeap(heap);
	ptr = HeapRemove(heap, Match, &arr[0]);
	TEST("Remove value: ", *(int*)ptr,  10);
	
	PrintHeap(heap);
	ptr = HeapRemove(heap, Match, &arr[9]);
	TEST("Remove value: ", *(int*)ptr,  100);
	
	PrintHeap(heap);
	ptr = HeapRemove(heap, Match, &arr[11]);
	TEST("Remove value: ", *(int*)ptr,  1);
	
	PrintHeap(heap);
	ptr = HeapRemove(heap, Match, &arr[5]);
	TEST("Remove value: ", *(int*)ptr,  60);
	
	PrintHeap(heap);
	ptr = HeapRemove(heap, Match, &arr[3]);
	TEST("Remove value: ", *(int*)ptr,  40);
	
	PrintHeap(heap);
	ptr = HeapRemove(heap, Match, &arr[2]);
	TEST("Remove value: ", *(int*)ptr,  30);
	
	PrintHeap(heap);
	ptr = HeapRemove(heap, Match, &arr[7]);
	TEST("Remove value: ", *(int*)ptr,  80);
	
	PrintHeap(heap);
	HeapDestroy(heap);
}

void Remove()
{
	      /*    0    1   2   3   4   5   6   7   8   9   10   11  */
	int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 5 , 1};
	
	heap_t *heap = HeapCreate(Compare);
	
	TEST("Size: ", HeapSize(heap), 0);
	
	TEST("Size: ", HeapIsEmpty(heap), 1);

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
	
	TEST("Size: ", HeapIsEmpty(heap), 0);

	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[5]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[7]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[9]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[0]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[11]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[10]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[8]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[3]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[4]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[1]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[6]);
	PrintHeap(heap);
	HeapRemove(heap, Match, &arr[3]);
	PrintHeap(heap);
	
	TEST("Size: ", HeapSize(heap), 1);
	TEST("Size: ", HeapIsEmpty(heap), 0);
	HeapDestroy(heap);
}
void GenPop()
{
       /*    0    1   2   3   4   5   6   7   8   9   10   11  */
	int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 5 , 1};
	
	heap_t *heap = HeapCreate(Compare);
	
	TEST("Size: ", HeapSize(heap), 0);
	TEST("Size: ", HeapIsEmpty(heap), 1);
	
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

	TEST("Size: ", HeapSize(heap), 12);
	TEST("Size: ", HeapIsEmpty(heap), 0);
	TEST("Peek: ", *(int*)HeapPeek(heap), 100);
	
	PrintHeap(heap);
	HeapPop(heap);
	TEST("Peek: ", *(int*)HeapPeek(heap), 90);
	PrintHeap(heap);
	HeapPop(heap);
	TEST("Peek: ", *(int*)HeapPeek(heap), 80);
	PrintHeap(heap);
	HeapPop(heap);
	TEST("Peek: ", *(int*)HeapPeek(heap), 70);
	PrintHeap(heap);
	TEST("Size: ", HeapSize(heap), 9);
	HeapPop(heap);
	PrintHeap(heap);
	HeapPop(heap);
	PrintHeap(heap);
	HeapPop(heap);
	PrintHeap(heap);
	HeapPop(heap);
	TEST("Peek: ", *(int*)HeapPeek(heap), 30);
	PrintHeap(heap);
	HeapPop(heap);
	PrintHeap(heap);
	HeapPop(heap);
	PrintHeap(heap);
	HeapPop(heap);
	TEST("Size: ", HeapSize(heap), 2);
	PrintHeap(heap);
	HeapPop(heap);
	TEST("Size: ", HeapSize(heap), 1);
	PrintHeap(heap);
	
	
	TEST("Size: ", HeapSize(heap), 1);
	TEST("Size: ", HeapIsEmpty(heap), 0);

	HeapPop(heap);
	
	PrintHeap(heap);

	HeapDestroy(heap);
	
}

