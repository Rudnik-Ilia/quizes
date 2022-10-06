
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <limits.h>/*CHAR_BIT*/

#include "fsa.h"

#define CAFE (void*) 0xCAFEBABE 

/*
struct fsa{
	size_t offset;
	size_t block_size;
}; 
*/



fsa_t *FSAInit(void *memory, size_t mem_size, size_t block_size)
{
	fsa_t* fsa = NULL;
	
	size_t freespace = 0;
	
	
	assert(0 != mem_size);
	assert(NULL != memory);
	
	fsa = (void*)((char*)memory + sizeof(fsa_t));
	
	fsa->block_size = (block_size - block_size % CHAR_BIT) + CHAR_BIT;
	fsa->offset = 0;
	freespace = ((mem_size - sizeof(fsa_t)) / fsa->block_size) * fsa->block_size;
	

	printf("%ld\n", freespace);

	return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
	void *memory = NULL;
	
	assert(NULL != fsa);
	
	memory = (char*)fsa + fsa->offset;
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
	fsa->offset = (char*)block_to_free - (char*)fsa;
}

size_t FSACountFree(const fsa_t *fsa)
{
	assert(NULL != fsa);
	/*
	return (fsa->freespace  - fsa->offset)/fsa->block_size;
	*/
	return 0;

}

























