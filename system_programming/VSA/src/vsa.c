
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
	return !(block_size % CHAR_BIT) ? block_size : (block_size - block_size % CHAR_BIT + CHAR_BIT);
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
	
	block = (block_t *)((char *)memory + SIZE_STR + freespace);
	block->size = 0;
	/*
*/
	printf("freespace: %ld\n", freespace);
	return vsa;
}


void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	block_t *b = (block_t *)vsa;
	size_t old_size = 0;
	long step = 0;
	void *memory = NULL;
	
	block_size = ResizeBlock(block_size);
	printf("b->size-1: %ld\n", b->size);
	
	while(0 != b->size)
	{
		printf("+\n");
		
		if((long)block_size <= b->size)
		{	
			if((long)block_size == b->size)
			{
				printf("equal\n");
				memory = (char *)b + SIZE_STR;
				old_size = b->size;
				b->size = block_size * -1;
				return memory;
				
			}
			printf("b->size-2: %ld\n", b->size);
			memory = (char *)b + SIZE_STR;
			old_size = b->size;
			printf("block_size: %ld\n", b->size);
			b->size = block_size * -1;
			printf("b->size-3: %ld\n", b->size);
			b = (block_t *)((char *)b + SIZE_STR + block_size);	
			
			b->size = old_size - block_size - SIZE_STR;

			return memory;
		}
		else
		{
			
			printf("-\n");
			
			step = b->size < 0 ? b->size * -1 : b->size;
			
			printf("tmp: %ld\n", step);	
			b = (block_t *)((char *)b + step + SIZE_STR);
			
		}
	}
	printf("END\n");
	return memory;
}



















