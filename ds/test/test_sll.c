
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
	(void)param;
	
	assert(NULL != data);
	assert(NULL != param);
	
	*(size_t*)data += 1;
	
	return 0;
}

int Match(void *data, void *params)
{
	(void)params;
	
	assert(NULL != data);
	assert(NULL != params);
	
	return *(int*)data < 0 ? 1: 0;
}

void Main_test()
{
	int arr[] = {10, 20, 30, 40, 50};
	int x = 77;
	
	int max = 100;
	int negative = -8;
	sorted_list_t *srtll = SortedLLCreate(CmpLowHigh);
	/*
	printf("%p\n",SortedLLBegin(srtll).dll_iter); 
	printf("%p\n", SortedLLEnd(srtll).dll_iter); 
	*/
	
	TEST("ADRESS",SortedLLBegin(srtll).dll_iter, SortedLLEnd(srtll).dll_iter); 
	
	 
	
	TEST("Equal adress start", 1, SortedLLIsEqualIter(SortedLLBegin(srtll), SortedLLEnd(srtll)));
	TEST("Equal isEmpty start", 1, SortedLLIsEmpty(srtll));
	TEST("Equal Size start", 0, SortedLLSize(srtll));
	
	
	SortedLLInsert(srtll, &arr[4]);
	TEST("Size", SortedLLSize(srtll), 1);
	SortedLLInsert(srtll, &arr[3]);
	TEST("Size", SortedLLSize(srtll), 2);
	SortedLLInsert(srtll, &arr[2]);
	TEST("Size", SortedLLSize(srtll), 3);
	
	TEST("First item",*(int*)SortedLLGetData(SortedLLBegin(srtll)), 30);
	
	SortedLLRemove(SortedLLBegin(srtll));
	
	TEST("AFTER REMOVE", *(int*)SortedLLGetData(SortedLLBegin(srtll)), 40);
	
	SortedLLForEach(SortedLLBegin(srtll), SortedLLEnd(srtll), &PlusOne, &arr[0]);
	
	TEST("AFTER + 1", *(int*)SortedLLGetData(SortedLLBegin(srtll)), 41);
	
	SortedLLInsert(srtll, &arr[2]);
	
	
	SortedLLPopFront(srtll);
	SortedLLPopBack(srtll);
	
	TEST("Size", SortedLLSize(srtll), 1);
	
	SortedLLInsert(srtll, &x);
	
	SortedLLInsert(srtll, &negative);
	
	
	SortedLLGetData(SortedLLFind(srtll, SortedLLBegin(srtll), SortedLLEnd(srtll), &max));
	
	TEST("FIND",*(int*)SortedLLGetData(SortedLLFind(srtll, SortedLLBegin(srtll), SortedLLPrev(SortedLLEnd(srtll)), &negative)), -8);
	
	TEST("FIND IF", *(int*)SortedLLGetData(SortedLLFindIf(SortedLLBegin(srtll), SortedLLPrev(SortedLLEnd(srtll)), &Match, &negative)), -8);
	
	
	SortedLLDestroy(srtll);
}

void TestMerge()
{
	int data_one = 1;
	int data_two = 3;
	int data_three = 5;
	
	int data1 = 2;
	int data2 = 4;
	int data3 = 6;
	
	sorted_list_t *srtll_src = SortedLLCreate(CmpLowHigh);
	sorted_list_t *srtll_dest = SortedLLCreate(CmpLowHigh);
	
	SortedLLInsert(srtll_src, &data_one);
	SortedLLInsert(srtll_src, &data_two);
	SortedLLInsert(srtll_src, &data_two);
	SortedLLInsert(srtll_src, &data_three);
	
	SortedLLInsert(srtll_dest, &data1);
	SortedLLInsert(srtll_dest, &data2);
	SortedLLInsert(srtll_dest, &data3);
	
	SortedLLMerge(srtll_dest, srtll_src);
/*
	printf("%d", *(int *)SortedLLGetData((SortedLLBegin(srtll_dest))));
	printf("%d", *(int *)SortedLLGetData(SortedLLNext(SortedLLBegin(srtll_dest))));
	printf("%d", *(int *)SortedLLGetData(SortedLLNext(SortedLLNext(SortedLLBegin(srtll_dest)))));
	printf("%d", *(int *)SortedLLGetData(SortedLLNext(SortedLLNext(SortedLLNext(SortedLLBegin(srtll_dest))))));
	printf("%d", *(int *)SortedLLGetData(SortedLLNext(SortedLLNext(SortedLLNext(SortedLLNext(SortedLLBegin(srtll_dest)))))));
	printf("%d", *(int *)SortedLLGetData(SortedLLNext(SortedLLNext(SortedLLNext(SortedLLNext(SortedLLNext(SortedLLBegin(srtll_dest))))))));
*/
	
	TEST("Final length", SortedLLSize(srtll_dest), 7);
	
	SortedLLDestroy(srtll_src);
	SortedLLDestroy(srtll_dest);
}


int main()
{
	Main_test();
	TestMerge();
	
	PASS;
	
return 0;
}










