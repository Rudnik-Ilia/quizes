
/**********************
* Title : FSA
* Author: Ilia Rudnik
* Reviewer: Alena
* Date : 12/10/2022
* Status : approved
**********************/

#include <stdio.h>
#include <assert.h>
#include <limits.h>/*CHAR_BIT*/

#include "vsa.h"

#define SIZE_STR sizeof(block_t)
/*
typedef struct block_header{

    	long size;
    
   	#ifndef NDEBUG
	
	#endif   
}block_t;
*/

static size_t ResizeBlock(size_t block_size)
{
	return !(block_size % CHAR_BIT) ? block_size : (block_size - block_size % CHAR_BIT + CHAR_BIT);
}

block_t *Next(block_t *block)
{
	long step = 0;
	
	assert(NULL != block);
	
	step = block->size < 0 ? block->size * -1 : block->size; 
	return (block_t *)((char *)block + SIZE_STR + step);
}

static void Defragment(block_t *block)
{
	block_t *next = NULL;
	assert(NULL != block);
	
	
	if(block >= 0)
	{
		next = Next(block);
		while(next->size > 0)
		{	
			block->size += SIZE_STR + next->size;
			next = Next(block);
		}
	}
	else
	{
		break;
	}
}

vsa_t *VSAInit(void *memory, size_t mem_size)
{	
	vsa_t *vsa = memory;
	block_t *block = NULL;
	size_t freespace = 0;
	assert(NULL != memory);
	
	block = (block_t *)memory;
	
	freespace = mem_size - SIZE_STR * 2;
	freespace -= freespace % CHAR_BIT;
	
	block->size = freespace;
	
	block = (block_t *)((char *)memory + SIZE_STR + freespace);
	block->size = 0;
	/*
*/
	printf("freespace: %ld\n", freespace);
	return vsa;
}


void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	block_t *b = NULL;
	void *memory = NULL;
	size_t old_size = 0;
	
	assert(NULL != vsa);
	
	b = (block_t *)vsa;
	
	block_size = ResizeBlock(block_size);
	
	while(0 != b->size )
	{
		if((long)block_size <= b->size)
		{	
			if((long)block_size == b->size)
			{
				memory = (char *)b + SIZE_STR;
				b->size *= -1;
				
				return memory;
				
			}
			memory = (char *)b + SIZE_STR;
			old_size = b->size;
			b->size = block_size * -1;
			b = Next(b);
		
			b->size = old_size - block_size - SIZE_STR;

			return memory;
		}
		else
		{	
			b = Next(b);	
		}
	}
	printf("END\n");
	return memory;
}

void VSAFree(void *block_to_free)
{	
	block_t *block = NULL;
	assert(NULL != block_to_free);
	
	block = (block_t *)((char *)block_to_free - SIZE_STR);
		
	printf("%d\n", block->size);

}

















