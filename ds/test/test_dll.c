

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
	DLLDestroy(list);
	DLLDestroy(output);	
}

void Test_for_Splice()
{
	int arr[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};

	
	dllist_t* list1 = DLLCreate();
	dllist_t* list2 = DLLCreate();
	
	printf("-------------------------------------------\n");
	printf("Test for Splice: \n");
	
	DLLPushFront(list1, &arr[0]);
	DLLPushFront(list1, &arr[1]);
	DLLPushFront(list1, &arr[2]);
	DLLPushFront(list1, &arr[3]);
	DLLPushFront(list1, &arr[4]);
	DLLPushFront(list1, &arr[5]);
	
	DLLPushFront(list2, &arr[6]);
	DLLPushFront(list2, &arr[7]);
	DLLPushFront(list2, &arr[8]);
	
	
	printf("Size:  %ld\n", DLLSize(list1));
	printf("Size:  %ld\n", DLLSize(list2));
	
	
	DLLSplice(DLLBegin(list1), DLLEnd(list1), DLLBegin(list2));
	
	
	printf("Size:  %ld\n", DLLSize(list1));
	printf("Size:  %ld\n", DLLSize(list2));

	printf("-------------------------------------------\n");
	DLLDestroy(list1);
	DLLDestroy(list2);
	
}

void Test_Main()
{
	int arr[] = {100, 200, 300, 400, 500};
	
	dllist_t* list = DLLCreate();
	
	printf("Compare two iterator: \n");
	TEST(DLLBegin(list), DLLEnd(list));
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	TEST(DLLIsEmpty(list), 1); 
	printf("Adding by one: \n");

	DLLInsert(DLLEnd(list), &arr[0]);
	TEST(DLLIsEmpty(list), 0); 
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	DLLInsert(DLLEnd(list), &arr[1]);
	TEST(DLLSize(list), 2);
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
	
	TEST(DLLSize(list), 5);
	
	DLLPushFront(list, &arr[1]);
	DLLPushFront(list, &arr[1]);
	DLLPushFront(list, &arr[1]);
	TEST(DLLSize(list), 8);
	DLLPopBack(list);
	DLLPopBack(list);
	DLLRemove(DLLEnd(list));
	TEST(DLLSize(list), 5);
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	printf("Test for size: \n");
	TEST(DLLSize(list),5);
	
	
	printf("Removing by one: \n");
	DLLRemove(DLLBegin(list));
	DLLRemove(DLLBegin(list));
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	printf("-------------------------------------------\n");
	
	printf("Test for PopFront: ");
	DLLSetData(DLLBegin(list), &arr[4]);
	TEST(*(int*)DLLPopFront(list), 500);
	printf("-------------------------------------------\n");
	
	printf("Test for size: \n");
	TEST(DLLSize(list), 2);
	
	printf("Test for foreach: \n");
	TEST(DLLForEach(DLLBegin(list), DLLEnd(list), &PlusOne, &arr[0]), 0);
	
	TEST(*(int*)DLLGetData(DLLBegin(list)), 401);
	
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
	DLLDestroy(list);
}




int main()
{

	Test_Main();
	Test_for_MultiFind();

	Test_for_Splice();

return 0;
}



