
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include "fsa.h"



/*
struct fsa{
	void *base;
	size_t offset;
	size_t block_size;
	size_t freespace;
}; 
*/



fsa_t *FSAInit(void *memory, size_t mem_size, size_t block_size)
{
	fsa_t* fsa = NULL;
	
	assert(NULL != memory);
	
	fsa = (fsa_t*)memory;
	fsa->base = (void*)(fsa + sizeof(fsa_t));
	fsa->freespace = mem_size - sizeof(fsa_t); /*???????????*/
	fsa->block_size = (block_size - block_size % 8) + 8;
	fsa->offset = 0;

	return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
	void *memory = NULL;
	
	assert(NULL != fsa);
	
	memory = (char*)fsa->base + fsa->offset;
	if(*(char*)memory)
	{
		fsa->offset = *(char*)memory;
	}
	else
	{	
		fsa->offset += fsa->block_size;
	}	
	
	printf("ID: %d\n", *(char*)memory);
	return memory;
}

void FSAFree(fsa_t *fsa, void *block_to_free)
{
	assert(NULL != fsa);
	assert(NULL != block_to_free);
	
	*(char*)block_to_free = fsa->offset;
	fsa->offset = (char*)block_to_free - (char*)fsa->base;
}

size_t FSACountFree(const fsa_t *fsa)
{
	assert(NULL != fsa);
	return (fsa->freespace  - fsa->offset)/fsa->block_size;

}

























