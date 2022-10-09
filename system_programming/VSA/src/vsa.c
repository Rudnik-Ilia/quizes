
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
	
	printf("%ld\n", freespace);

	return vsa;
}























