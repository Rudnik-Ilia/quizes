
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <limits.h>/*CHAR_BIT*/

#include "fsa.h"


/*
struct fsa{
	size_t offset;
}; 
*/
size_t static ResizeBlock(size_t block_size)
{
	return (block_size - block_size % CHAR_BIT) + CHAR_BIT;
}


fsa_t *FSAInit(void *memory, size_t mem_size, size_t block_size)
{
	fsa_t* fsa = NULL;
	size_t i = 0;
	size_t number_of_blocks = 0;
	size_t tmp_offset = sizeof(fsa_t);
	
	assert(0 != mem_size);
	assert(NULL != memory);
	
	fsa = (fsa_t *)memory;
	fsa->offset = tmp_offset;
	
	block_size = ResizeBlock(block_size);
	number_of_blocks = (mem_size - tmp_offset)/block_size;
	
	
	for(; i < number_of_blocks - 1; ++i)
	{	
		*(size_t*)((char*)fsa + tmp_offset) = tmp_offset + block_size;
		tmp_offset += block_size;
		
	}
	printf("OFF:%ld\n", fsa->offset);
	
	printf("%ld\n", block_size);
	printf("%ld\n", number_of_blocks);

	return fsa;
	
/*
	(void *)((size_t)fsa->base + offset) = 0;
	freespace = ((mem_size - sizeof(fsa_t)) / block_size) * block_size;
	size_t freespace = 0;
	
*/
}
	
	


void *FSAAlloc(fsa_t *fsa)
{
	void *memory = NULL;

	
	assert(NULL != fsa);
	
	memory = (void *)((char *)fsa + fsa->offset);
	
	printf("ID: %ld\n", *(size_t *)memory);
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

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return ResizeBlock(block_size)*num_of_blocks + sizeof(fsa_t);
}

























