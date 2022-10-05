
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
	fsa_t* fsa = (fsa_t*)memory;
	fsa->base = (void*)(fsa + sizeof(fsa_t));
	fsa->freespace = mem_size - sizeof(fsa_t);
	fsa->block_size = (block_size - block_size % 8) + 8;
	
	fsa->offset = 0;

	return fsa;
}



size_t FSACountFree(const fsa_t *fsa)
{
	assert(NULL != fsa);
	return (fsa->freespace / fsa->block_size) - (fsa->offset/8);
}


