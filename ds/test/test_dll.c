

#include <stdio.h>
#include <assert.h>

#include "utils.h"
#include "dll.h"




int MatchParam(const void *data, void *params)
{
	assert(data);
	assert(params);
	return *(int*)data == *(int*)params;
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


	
void Test_for_MultiFind()
{
	int arr[] = {100, 200, 100, 400, 100};
	dllist_t* list = DLLCreate();
	dllist_t* output = DLLCreate();
	dllist_iter_t tmp = DLLBegin(output);
	printf("-------------------------------------------\n");
	printf("Test for Multyfind: \n");
	
	DLLPushFront(list, &arr[0]);
	DLLPushFront(list, &arr[1]);
	DLLPushFront(list, &arr[2]);
	DLLPushFront(list, &arr[3]);
	DLLPushFront(list, &arr[4]);
	TEST(DLLMultiFind(DLLBegin(list), DLLEnd(list), &MatchParam, &arr[0], output), 3);
	while(!DLLIsEqualIter(tmp, DLLEnd(output)))
	{
		TEST(*(int*)DLLGetData(tmp), 100);
		tmp = DLLNext(tmp);
	
	}
	printf("-------------------------------------------\n");
		
}

void Test_for_Splice()
{
	int arr[] = {100, 200, 300, 400, 500, 600, 700, 800};
	
	dllist_iter_t iter1 = NULL;
	dllist_iter_t iter2 = NULL;
	dllist_iter_t iter3 = NULL;
	
	dllist_t* list1 = SpecialDLLCreate();
	dllist_t* list2 = SpecialDLLCreate();
	dllist_iter_t tmp = NULL;
	
	
	
	printf("-------------------------------------------\n");
	printf("Test for Multyfind: \n");
	
	DLLPushFront(list1, &arr[0]);
	DLLPushFront(list1, &arr[1]);
	DLLPushFront(list1, &arr[2]);
	DLLPushFront(list1, &arr[3]);
	DLLPushFront(list1, &arr[4]);
	DLLPushFront(list1, &arr[5]);
	
	DLLPushFront(list2, &arr[6]);
	DLLPushFront(list2, &arr[7]);
	
	/*
	while(!DLLIsEqualIter(tmp, DLLEnd(list2)))
	{
		printf("%d\n", *(int*)DLLGetData(tmp));
		tmp = DLLNext(tmp);
	
	tmp = DLLNext(DLLBegin(list2));
	}
	
	
	*/
	printf("Size:  %ld\n", DLLSize(list1));
	printf("Size:  %ld\n", DLLSize(list2));
	
	iter1 = DLLNext(DLLNext(DLLBegin(list1)));
	iter2 = DLLPrev(DLLEnd(list1));
	iter3 = DLLNext(DLLBegin(list2));
	
	DLLSplice(iter1, iter2, iter3);
	
	printf("Size:  %ld\n", DLLSize(list1));
	printf("Size:  %ld\n", DLLSize(list2));
	
	printf("-------------------------------------------\n");

}






int main()
{

	int arr[] = {100, 200, 300, 400, 500};
	
	dllist_t* list = DLLCreate();
	
	
	printf("Compare two iterator: ");
	printf("%d\n", DLLIsEqualIter(DLLBegin(list), DLLEnd(list)));
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	printf("%d\n", DLLIsEmpty(list)); 
	printf("Adding by one: \n");

	DLLInsert(DLLEnd(list), &arr[0]);
	
	printf("%d\n", DLLIsEmpty(list)); 
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	DLLInsert(DLLEnd(list), &arr[1]);
	printf("-------------------------------------------\n");
	printf("Compare two iterator: ");
	printf("%d\n", DLLIsEqualIter(DLLBegin(list), DLLEnd(list)));
	
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	DLLInsert(DLLEnd(list), &arr[2]);
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	printf("Test for find: \n ");
	printf("%d\n", *(int*)DLLGetData(DLLFind(DLLBegin(list), DLLEnd(list), &MatchParam, &arr[2])));
	
	DLLInsert(DLLBegin(list), &arr[3]);
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	printf("-------------------------------------------\n");
	printf("Test for find: \n ");
	
	printf("%d\n", *(int*)DLLGetData(DLLFind(DLLBegin(list), DLLEnd(list), &MatchParam, &arr[2])));
	
	printf("-------------------------------------------\n");
	
	DLLPushBack(list, &arr[1]);
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	printf("Size:  %ld\n", DLLSize(list));
	
	DLLPushFront(list, &arr[1]);
	DLLPushFront(list, &arr[1]);
	DLLPushFront(list, &arr[1]);
	printf("Size:  %ld\n", DLLSize(list));
	DLLPopBack(list);
	DLLPopBack(list);
	DLLRemove(DLLEnd(list));
	printf("Size:  %ld\n", DLLSize(list));
	
	
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	printf("Test for size: \n");
	printf("%ld\n", DLLSize(list));
	
	
	printf("Removing by one: \n");
	DLLRemove(DLLBegin(list));
	DLLRemove(DLLBegin(list));
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	printf("-------------------------------------------\n");
	
	printf("Test for PopFront: ");
	DLLSetData(DLLBegin(list), &arr[4]);
	printf("%d\n",*(int*)DLLPopFront(list));
	printf("-------------------------------------------\n");
	
	printf("Test for size: \n");
	printf("Size:  %ld\n", DLLSize(list));
	
	printf("Test for foreach: \n");
	printf("%d\n",DLLForEach(DLLBegin(list), DLLEnd(list), &PlusOne, &arr[0]));
	
	printf("%d\n",*(int*)DLLGetData(DLLBegin(list)));
	
	
	DLLRemove(DLLEnd(list));
	DLLPushFront(list, &arr[1]);
	
	DLLRemove(DLLBegin(list));
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	printf("-------------------------------------------\n");
	
	DLLRemove(DLLBegin(list));
	printf("-------------------------------------------\n");
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	printf("-------------------------------------------\n");
	
	printf("Removing the iast one: \n");
	printf("Size:  %ld\n", DLLSize(list));
	DLLPushFront(list, &arr[1]);
	DLLRemove(DLLBegin(list));
	DLLPushFront(list, &arr[1]);
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	printf("Size:  %ld\n", DLLSize(list));
	DLLRemove(DLLEnd(list));
	printf("Size:  %ld\n", DLLSize(list));
	
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	printf("-------------------------------------------\n");
	
	Test_for_MultiFind();
	
	Test_for_Splice();
	
	




return 0;
}



