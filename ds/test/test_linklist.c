
#include <limits.h> /* CHARBIT */
#include <assert.h> /* assert */
#include <string.h> /* strrev */

#include "../include/SLL.h"
#include "../include/MYHEAD.h"

#define ERROR(str) fprintf(stderr, str)

int MatchParam(const void *data, void *param)
{
	assert(data);
	assert(param);
	return *(char*)data == *(char*)param;
} 

is_match_func is_match = &MatchParam;


int main()
{	
	char c = 'x';
	char arr[] = {'A','B','C','D','E','F','G'};
	sll_t* Mylist = SllCreate();
	iterator_t iterator = SllBegin(Mylist);
	TEST(SllBegin(Mylist), SllEnd(Mylist));
	
	/*
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	
	printf("%d\n", SllIsEmpty(Mylist)); 
	
	printf("%p\n", SllNext(iterator)); 
	SllSetData(iterator, &c);
	printf("%c\n", *(char*)(SllGetData(iterator)));
	SllFind(SllBegin(Mylist), SllEnd(Mylist), is_match, &arr[1]);
	*/
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	printf("%ld\n", SllCount(Mylist));
	
	printf("Adding 3 item: \n");
	SllInsert(iterator, &arr[0]);
	SllInsert(iterator, &arr[1]); 
	SllInsert(iterator, &arr[2]);
	
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	printf("%ld\n", SllCount(Mylist));
	printf("---------------------------------------------\n");
	
	
	printf("%c\n", *(char*)(SllGetData(SllFind(SllBegin(Mylist), SllEnd(Mylist), is_match, &arr[1]))));
	/*
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	printf("%ld\n", SllCount(Mylist));
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	printf("%ld\n", SllCount(Mylist));
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	printf("%ld\n", SllCount(Mylist));
	printf("---------------------------------------------\n");
	
	printf("Removing 1 item: \n");
	SllRemove(iterator);
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	printf("%ld\n", SllCount(Mylist));
	printf("---------------------------------------------\n");
	
	*/
	
	
	
	
	












return 0;
}
