
#include <stdio.h>

#include "heap.h"
#include "test.h"

#define CAPACITY 10


int Compare(const void * p1, const void * p2)
{
	return *(int*)p1 - *(int*)p2;
}


int main()
{
	heap_t *heap = HeapCreate(Compare, sizeof(int));
	
	TEST("Size: ", HeapSize(heap), 0);
	TEST("Size: ", HeapIsEmpty(heap), 0);
	

	HeapDestroy(heap);
return 0;
}
