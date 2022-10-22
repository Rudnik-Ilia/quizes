
#include <limits.h> /* CHARBIT */
#include <assert.h> /* assert */
#include <string.h> /* strrev */

#include "SLL.h"
#include "utils.h"


int MatchParam(const void *data, void *param)
{
	assert(NULL != data);
	assert(NULL != param);
	return *(int*)data == *(int*)param;
}

int Act(void *data, void *param)
{
	int tmp = *(int*)data;
	int st = 1;
	assert(data);
	assert(param);
	*(int*)(data)*= *(int*)(param);
	if(tmp == *(int*)(data))
	{
		st = 0;
	}
	return st;
}
 
is_match_func is_match = &MatchParam;
action_func func = &Act;

void Test_Main();
void Test_Append();	
int main()
{	
	Test_Main();
	Test_Append();	


	
return 0;
}

void Test_Main()
{	
	int x = 100;
	int ins = 888;
	int arr[] = {1,2,3,4,5,6,7};
	sll_t* Mylist = SllCreate();
	iterator_t iterator = SllBegin(Mylist);
	iterator_t temp2 = SllBegin(Mylist);
	
	printf("Main test: \n");
	TEST_EQUAL(SllBegin(Mylist), SllEnd(Mylist));
	
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST_EQUAL(SllCount(Mylist), 0);
	
	printf("Adding 3 item: \n");
	SllInsert(iterator, &arr[0]);
	SllInsert(iterator, &arr[1]); 
	SllInsert(iterator, &arr[2]);

	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST_EQUAL(SllCount(Mylist), 3);
	printf("---------------------------------------------\n");

	TEST_EQUAL(*(int*)(SllGetData(SllFind(SllBegin(Mylist), SllEnd(Mylist), is_match, &arr[1]))), 2);
	
	SllForEach(SllBegin(Mylist), SllEnd(Mylist), func, &x);
	
	TEST_EQUAL(*(int*)(SllGetData(iterator)), 300);
	
	SllInsert(iterator, &ins);
	TEST_EQUAL(*(int*)(SllGetData(iterator)), 888);
	printf("---------------------------------------------\n");
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST_EQUAL(SllCount(Mylist), 3);
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST_EQUAL(SllCount(Mylist), 2);
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST_EQUAL(SllCount(Mylist), 1);
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST_EQUAL(SllCount(Mylist), 0);
	printf("---------------------------------------------\n");
	
	
	for(;temp2 != SllEnd(Mylist); temp2 = SllNext(temp2))
	{
		temp2 = SllRemove(temp2);
	}
	          
	
	SllDestroy(Mylist);
}

void Test_Append()
{
	int arr[] = {1,2,3,4,5,6,7};
	sll_t* Mylist = SllCreate();
	sll_t* list_2 = SllCreate();
	
	iterator_t iterator = SllBegin(Mylist);
	iterator_t iterator_2 = SllBegin(list_2);
	printf("Append test: \n");
	
	SllInsert(iterator, &arr[0]);
	SllInsert(iterator, &arr[1]); 
	SllInsert(iterator, &arr[2]);
	
	SllInsert(iterator_2, &arr[0]);
	SllInsert(iterator_2, &arr[1]); 
	SllInsert(iterator_2, &arr[2]);
	
	TEST_EQUAL(SllCount(Mylist),3);
	TEST_EQUAL(SllCount(list_2),3);
	
	SllAppend(Mylist, list_2); 
	
	TEST_EQUAL(SllCount(Mylist), 6);
	TEST_EQUAL(SllCount(list_2), 0);
	
	SllDestroy(Mylist);
	SllDestroy(list_2);
}















