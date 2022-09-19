
#include <stdio.h>  /* printf */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "srtll.h"
#include "utils.h"
#include "test.h"
#include "dll.h"

int CmpLowHigh(const void *data1, const void *data2)
{	
	return *(int*)data1 - *(int*)data2;
}


int main()
{
	sorted_list_t *srtll = SortedLLCreate(CmpLowHigh);
	
	printf("%p\n", SortedLLBegin(srtll).dll_iter); 
	printf("%p\n", SortedLLEnd(srtll).dll_iter); 
	
	printf("%p\n", SortedLLNext(SortedLLEnd(srtll)).dll_iter);
	printf("%p\n", SortedLLPrev(SortedLLBegin(srtll)).dll_iter);  
	
	TEST("Equal adress start", 1, SortedLLIsEqualIter(SortedLLBegin(srtll), SortedLLEnd(srtll)));
	TEST("Equal isEmpty start", 1, SortedLLIsEmpty(srtll));
	TEST("Equal Size start", 0, SortedLLSize(srtll));
	
	
	
	
	
	SortedLLDestroy(srtll);
	
	return 0;
}

