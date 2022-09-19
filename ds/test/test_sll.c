
#include <stdio.h>  /* printf */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "srtll.h"
#include "utils.h"
#include "test.h"
#include "dll.h"

int Foo(const void *data_one, const void *data_two)
{	
	(void)data_one;
	(void)data_two;
	return 0;
}

int main()
{
	sorted_list_t *srtll = SortedLLCreate(Foo);
	
	printf("%p\n", SortedLLBegin(srtll)); 
	printf("%p\n", SortedLLEnd(srtll)); 
	
	
	
	return 0;
}

