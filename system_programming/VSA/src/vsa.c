
/**********************
* Title : FSA
* Author: Ilia Rudnik
* Reviewer: Olga
* Date : 12/10/2022
* Status : approved
**********************/

#include <stdio.h>
#include <assert.h>
#include <limits.h>/*CHAR_BIT*/

#include "vsa.h"


typedef struct block_header{

    	long size;
    
   	#ifndef NDEBUG
	
	#endif   
}block_t;


static size_t ResizeBlock(size_t block_size)
{
	return !(block_size % CHAR_BIT) ? block_size : (block_size - block_size % CHAR_BIT) + CHAR_BIT;
}


vsa_t *VSAInit(void *memory, size_t mem_size)
{
	block_t * block = NULL;
	size_t freespace = 0;
	assert(NULL != memory);
	
	block = (block_t *)memory;
	
	freespace = mem_size - (sizeof(block_t) * 2);
	
	
	printf("%ld\n", sizeof(block_t) * 2);
	
	
	return memory;
}
