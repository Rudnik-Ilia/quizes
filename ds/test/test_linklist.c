#include <stdio.h>  /* printf */
#include <limits.h> /* CHARBIT */
#include <assert.h> /* assert */
#include <string.h> /* strrev */

#include "../include/SLL.h"


#define ERROR(str) fprintf(stderr, str)

int main()
{	
	char arr[] = {'A','B','C','D','E','F','G'};
	sll_t* Mylist = SllCreate();
	iterator_t iterator = SllBegin(Mylist);
	
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	printf("%d\n", SllIsEmpty(Mylist)); 
	
	printf("%p\n", SllNext(iterator)); 
	
	/*
	*/
	  
	
	SllInsert(iterator, &arr[0]);
	printf("%p\n", SllNext(iterator)); 
	SllInsert(iterator, &arr[1]);
	printf("%p\n", SllNext(iterator)); 
	
	
	
	printf("%p\n", SllBegin(Mylist));
	printf("%p\n", SllEnd(Mylist)); 
	
	
	printf("%c\n", *(char*)(SllGetData(iterator)));
	ERROR("error");
	
	
	
	












return 0;
}
