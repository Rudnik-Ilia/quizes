
#include <stdio.h>
#include <stdlib.h> /*malloc*/

#include "fsa.h"





int main()
{
	fsa_t *fsa = NULL;
	
	void *space = (void *)malloc(100);
	if(NULL == space)
	{
		puts("ERROR!");
	}
	
	fsa = FSAInit(space, 100, 10);
	
	printf("%p\n", space);
	printf("%p\n", fsa);
	printf("%p\n", fsa->base);
	
	printf("offset: %ld\n", fsa->offset);
	printf("count: %ld\n", fsa->count);
	printf("freespace: %ld\n", fsa->freespace);
	printf("block size: %ld\n", fsa->block_size);
	
	printf("count: %ld\n", FSACountFree(fsa));
	


return 0;
}
