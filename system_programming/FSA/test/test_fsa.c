
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
	void *block4 = NULL;
	void *block5 = NULL;
	void *block6 = NULL;
	void *block7 = NULL;
	
	void *space = (void *)malloc(100);
	if(NULL == space)
	{
		puts("ERROR!");
	}
	
	fsa = FSAInit(space, 100, 10);
	printf("offset: %ld\n", fsa->offset);
	printf("BASE: %p\n", fsa);
	printf("BASE: %p\n", fsa + fsa->offset);
	
	
	
	printf("---------------------------------------------\n");
	block1 = FSAAlloc(fsa);
	assert(NULL != block1);
	printf("BASE: %p\n", fsa + fsa->offset);	
	printf("Block: %p\n", block1);
	printf("offset: %ld\n", fsa->offset);

	
	printf("---------------------------------------------\n");
	block2 = FSAAlloc(fsa);
	assert(NULL != block2);
	printf("BASE: %p\n", fsa + fsa->offset);	
	printf("Block: %p\n", block2);
	printf("offset: %ld\n", fsa->offset);


	printf("---------------------------------------------\n");
	block3 = FSAAlloc(fsa);
	assert(NULL != block3);
	printf("Block: %p\n", block3);
	printf("BASE: %p\n", fsa + fsa->offset);	
	printf("offset: %ld\n", fsa->offset);


	printf("---------------------------------------------\n");
	block4 = FSAAlloc(fsa);
	printf("BASE: %p\n", fsa + fsa->offset);	
	printf("Block: %p\n", block4);
	printf("offset: %ld\n", fsa->offset);

	printf("---------------------------------------------\n");
	block5 = FSAAlloc(fsa);
	printf("BASE: %p\n", fsa + fsa->offset);	
	printf("Block: %p\n", block5);
	printf("offset: %ld\n", fsa->offset);
	
	printf("---------------------------------------------\n");
	block6 = FSAAlloc(fsa);
	printf("BASE: %p\n", fsa + fsa->offset);	
	printf("Block: %p\n", block6);
	printf("offset: %ld\n", fsa->offset);
	
	printf("---------------------------------------------\n");
	block7 = FSAAlloc(fsa);
	printf("BASE: %p\n", fsa + fsa->offset);	
	printf("Block: %p\n", block7);
	printf("offset: %ld\n", fsa->offset);
	
	printf("---------------------------------------------\n");
	FSAFree(fsa, block4);
	printf("Block: %p\n", block4);
	printf("BASE: %p\n", fsa);	
	printf("offset: %ld\n", fsa->offset);
	
	
	printf("---------------------------------------------\n");
	FSAFree(fsa, block3);
	printf("Block: %p\n", block3);
	printf("BASE: %p\n", fsa);	
	printf("offset: %ld\n", fsa->offset);
	
	
	
	
	free(space);
return 0;
}
