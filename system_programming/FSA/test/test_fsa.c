
#include <stdio.h>
#include <stdlib.h> /*malloc*/
#include <assert.h>

#include "fsa.h"





int main()
{
	fsa_t *fsa = NULL;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	
	void *tmp = NULL;
	
	void *space = (void *)calloc(100, 1);
	if(NULL == space)
	{
		puts("ERROR!");
	}
	
	fsa = FSAInit(space, 100, 10);
	
	printf("%p\n", space);
	printf("FSA: %p\n", fsa);
	printf("BASE: %p\n", fsa->base);
	
	printf("offset: %ld\n", fsa->offset);
	printf("freespace: %ld\n", fsa->freespace);
	printf("block size: %ld\n", fsa->block_size);
	printf("count: %ld\n", FSACountFree(fsa));
	
	printf("---------------------------------------------\n");
	block1 = FSAAlloc(fsa);
	assert(NULL != block1);
	printf("Block: %p\n", block1);
	printf("BASE: %p\n", fsa->base);
	
	
	printf("offset: %ld\n", fsa->offset);
	printf("freespace: %ld\n", fsa->freespace);
	printf("block size: %ld\n", fsa->block_size);
	printf("count: %ld\n", FSACountFree(fsa));
	
	printf("---------------------------------------------\n");
	block2 = FSAAlloc(fsa);
	assert(NULL != block2);
	printf("Block: %p\n", block2);
	printf("BASE: %p\n", fsa->base);
	
	
	printf("offset: %ld\n", fsa->offset);
	printf("freespace: %ld\n", fsa->freespace);
	printf("block size: %ld\n", fsa->block_size);
	printf("count: %ld\n", FSACountFree(fsa));
	
	
	printf("---------------------------------------------\n");
	block3 = FSAAlloc(fsa);
	assert(NULL != block3);
	printf("Block: %p\n", block3);
	printf("BASE: %p\n", fsa->base);
	
	
	printf("offset: %ld\n", fsa->offset);
	printf("freespace: %ld\n", fsa->freespace);
	printf("block size: %ld\n", fsa->block_size);
	printf("count: %ld\n", FSACountFree(fsa));
	
	printf("---------------------------------------------\n");
	FSAFree(fsa, block2);
	printf("Block: %p\n", block2);
	printf("BASE: %p\n", fsa->base);
	
	
	printf("offset: %ld\n", fsa->offset);
	printf("freespace: %ld\n", fsa->freespace);
	printf("block size: %ld\n", fsa->block_size);
	printf("count: %ld\n", FSACountFree(fsa));
	
	printf("---------------------------------------------\n");
	tmp = FSAAlloc(fsa);
	printf("Block: %p\n", tmp);
	printf("BASE: %p\n", fsa->base);
	
	
	printf("offset: %ld\n", fsa->offset);
	printf("freespace: %ld\n", fsa->freespace);
	printf("block size: %ld\n", fsa->block_size);
	printf("count: %ld\n", FSACountFree(fsa));

return 0;
}
