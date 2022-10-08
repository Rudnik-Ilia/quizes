
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
	printf("BASE start: %p\n", (void*)fsa);
	printf("BASE + off: %p\n", (void*)(fsa + 8));
	printf("SIZE: %ld\n", FSACountFree(fsa));
	
	printf("DIFF: %ld\n", (size_t*)block2 - (size_t*)(fsa + 8));
	
	
	
	printf("---------------------------------------------\n");
	block1 = FSAAlloc(fsa);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block1);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));

	
	printf("---------------------------------------------\n");
	block2 = FSAAlloc(fsa);
	assert(NULL != block2);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block2);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));

	printf("DIFF: %ld\n", (size_t*)block2 - (size_t*)(fsa + 8));

	printf("---------------------------------------------\n");
	block3 = FSAAlloc(fsa);
	assert(NULL != block3);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block3);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));


	printf("---------------------------------------------\n");
	block4 = FSAAlloc(fsa);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block4);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));

	printf("---------------------------------------------\n");
	block5 = FSAAlloc(fsa);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block5);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));
	
	printf("---------------------------------------------\n");
	block6 = FSAAlloc(fsa);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block6);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));
	
	printf("---------------------------------------------\n");
	block7 = FSAAlloc(fsa);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block7);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));
	
	printf("---------------------------------------------\n");
	FSAFree(fsa, block2);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block1);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));
	
	printf("DIFF: %ld\n", (size_t*)block2 - (size_t*)(fsa + 8));
	
	printf("---------------------------------------------\n");
	FSAFree(fsa, block3);
	printf("BASE: %p\n", (void*)(fsa + 8));	
	printf("Block: %p\n", block3);
	printf("offset: %ld\n", fsa->offset);
	printf("SIZE: %ld\n", FSACountFree(fsa));
	
	printf("DIFF: %ld\n", (size_t*)block2 - (size_t*)(fsa + 8));
	
	free(space);
return 0;
}
