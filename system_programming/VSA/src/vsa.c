
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

typedef struct block_header{

    	long size;
    
   	#ifndef NDEBUG
	
	#endif   
}block_t;


static size_t ResizeBlock(size_t block_size)
{
	return !(block_size % CHAR_BIT) ? (long)block_size : (long)((block_size - block_size % CHAR_BIT) + CHAR_BIT);
}


vsa_t *VSAInit(void *memory, size_t mem_size)
{	
	vsa_t *vsa = memory;
	block_t * block = NULL;
	size_t freespace = 0;
	assert(NULL != memory);
	
	block = (block_t *)memory;
	
	freespace = mem_size - (sizeof(block_t) * 2);
	freespace -= freespace % CHAR_BIT;
	
	block->size = freespace;
	
	block = (block_t *)((char *)memory + sizeof(block_t) + freespace);
	block->size = 0;
	/*
	printf("%ld\n", freespace);
*/
	return vsa;
}


void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	block_t *b = (block_t *)vsa;
	size_t old_size = 0;
	void *memory = NULL;
	
	block_size = ResizeBlock(block_size);
	
	while(0 != b->size)
	{
		if(0 == b->size)
		{
			return NULL;
		} 
		else if((long)block_size <= b->size)
		{	
			
			memory = (char *)b + SIZE_STR;
			
			old_size = b->size;
			
			b->size = block_size * -1;

			b = (block_t *)((char *)b + SIZE_STR + block_size);	
			
			b->size = old_size - block_size - SIZE_STR;

			return memory;
		}
		else
		{
			if(b->size < 0)
			{
				b->size *= -1;
			}
			b = (block_t *)((char *)b + b->size + SIZE_STR);
			
		}
	}
	
	return NULL;
}




















