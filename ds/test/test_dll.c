

#include <stdio.h>

#include "utils.h"
#include "dll.h"
#include "utils.h"



int main()
{
	size_t i;
	int arr[] = {100, 200, 300, 400, 500};
	
	dllist_t* list = DLLCreate();
	dllist_iter_t iter = DLLEnd(list);
	
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
	
	DLLInsert(DLLEnd(list), &arr[0]);
	
	printf("Compare two iterator: ");
	printf("%d\n", DLLIsEqualIter(DLLBegin(list), DLLEnd(list)));
	
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	DLLInsert(DLLEnd(list), &arr[0]);
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	
	DLLInsert(DLLBegin(list), &arr[0]);
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	
	DLLPushBack(list, &arr[1]);
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	DLLPushFront(list, &arr[1]);
	
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
	printf("%ld\n", DLLSize(list));
	
	
	
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
	
	
	printf("%p\n", (void*)DLLBegin(list));
	printf("%p\n", (void*)DLLEnd(list)); 
	
	
	/*
	
	DLLInsert(DLLBegin(list), &arr[1]);
	
	*/
	
	




return 0;
}



