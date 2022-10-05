
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
	
	printf("%ld\n", fsa->offset);
	printf("%ld\n", fsa->count);
	printf("%ld\n", fsa->freespace);
	printf("%ld\n", fsa->block_size);
	


return 0;
}
