
#include <limits.h> /* CHARBIT */
#include <assert.h> /* assert */
#include <string.h> /* strrev */

#include "../include/SLL.h"
#include "../include/MYHEAD.h"

#define ERROR(str) fprintf(stderr, str)

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
	
	
	
	
	
	
	












return 0;
}
