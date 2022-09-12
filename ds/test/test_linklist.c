
#include <limits.h> /* CHARBIT */
#include <assert.h> /* assert */
#include <string.h> /* strrev */

#include "SLL.h"
#include "utils.h"


int MatchParam(const void *data, void *param)
{
	assert(data);
	assert(param);
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

int main()
{	
	int x = 100;
	int ins = 888;
	int arr[] = {1,2,3,4,5,6,7};
	sll_t* Mylist = SllCreate();
	iterator_t iterator = SllBegin(Mylist);
	
	TEST(SllBegin(Mylist), SllEnd(Mylist));
	
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST(SllCount(Mylist), 0);
	
	printf("Adding 3 item: \n");
	SllInsert(iterator, &arr[0]);
	SllInsert(iterator, &arr[1]); 
	SllInsert(iterator, &arr[2]);
	
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST(SllCount(Mylist), 3);
	printf("---------------------------------------------\n");
	
	
	
	TEST(*(int*)(SllGetData(SllFind(SllBegin(Mylist), SllEnd(Mylist), is_match, &arr[1]))), 2);
	
	SllForEach(SllBegin(Mylist), SllEnd(Mylist), func, &x);
	
	TEST(*(int*)(SllGetData(iterator)), 300);
	
	SllInsert(iterator, &ins);
	TEST(*(int*)(SllGetData(iterator)), 888);
	printf("---------------------------------------------\n");
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST(SllCount(Mylist), 3);
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST(SllCount(Mylist), 2);
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST(SllCount(Mylist), 1);
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", (void*)SllBegin(Mylist));
	printf("%p\n", (void*)SllEnd(Mylist)); 
	TEST(SllCount(Mylist), 0);
	printf("---------------------------------------------\n");
	
	SllDestroy(Mylist);

return 0;
}
