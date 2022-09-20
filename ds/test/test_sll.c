
#include <stdio.h>  /* printf */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "srtll.h"
#include "utils.h"
#include "test.h"
#include "dll.h"

int CmpLowHigh(const void *new, const void *old)
{	
	return *(int*)new - *(int*)old;
}

static int PlusOne(void *data, void *param)
{
	size_t tmp = *(size_t*)data;
	int status  = 0;
	(void)param;
	assert(param);
	*(size_t*)data += 1;
	if(tmp == *(size_t*)data)
	{
		status = 1;
	}
	return status;
}


int main()
{
	
	int arr[] = {10, 20, 30, 40, 50};
	sorted_list_t *srtll = SortedLLCreate(CmpLowHigh);
	
	printf("%p\n", SortedLLBegin(srtll).dll_iter); 
	printf("%p\n", SortedLLEnd(srtll).dll_iter); 
	
	printf("%p\n", SortedLLNext(SortedLLEnd(srtll)).dll_iter);
	printf("%p\n", SortedLLPrev(SortedLLBegin(srtll)).dll_iter);  
	
	TEST("Equal adress start", 1, SortedLLIsEqualIter(SortedLLBegin(srtll), SortedLLEnd(srtll)));
	TEST("Equal isEmpty start", 1, SortedLLIsEmpty(srtll));
	TEST("Equal Size start", 0, SortedLLSize(srtll));
	
	
	SortedLLInsert(srtll, &arr[4]);
	TEST("Size", SortedLLSize(srtll), 1);
	SortedLLInsert(srtll, &arr[3]);
	TEST("Size", SortedLLSize(srtll), 2);
	SortedLLInsert(srtll, &arr[2]);
	TEST("Size", SortedLLSize(srtll), 3);
	
	printf("%d\n", *(int*)SortedLLGetData(SortedLLBegin(srtll)));
	
	SortedLLRemove(SortedLLBegin(srtll));
	
	printf("%d\n", *(int*)SortedLLGetData(SortedLLBegin(srtll)));
	
	SortedLLForEach(SortedLLBegin(srtll), SortedLLEnd(srtll), &PlusOne, &arr[0]);
	
	printf("%d\n", *(int*)SortedLLGetData(SortedLLBegin(srtll)));
	
	SortedLLInsert(srtll, &arr[2]);
	
	
	SortedLLPopFront(srtll);
	SortedLLPopBack(srtll);
	
	TEST("Size", SortedLLSize(srtll), 1);
	
	
	
	
	
	SortedLLDestroy(srtll);
	PASS; 
	return 0;
}

