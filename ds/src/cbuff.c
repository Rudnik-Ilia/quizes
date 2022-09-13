/**********************
* Title : Worksheet 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/

#include <stdio.h>
#include <stddef.h> /* size_t*/
#include <stdlib.h> 
#include <string.h> /* memcpy */
#include <assert.h>

#include "cbuff.h"

struct cbuff{
	
	size_t capacity;
	size_t read;
	size_t write;
	char buffer[1];

};
static void buf_reset(cbuff_t *cbuff);

cbuff_t *CBuffCreate(size_t capacity)
{
	cbuff_t * new_cbuff = malloc(sizeof(cbuff_t*) + capacity);
	if(NULL == new_cbuff)
	{
		return 0;
	}
	new_cbuff->capacity = capacity;
	
	buf_reset(new_cbuff);
	return new_cbuff;	

}

ssize_t CBuffWrite(cbuff_t *cbuff, const void *src, size_t num_of_bytes)
{
	assert(cbuff);
	assert(src);
	
	memcpy(&cbuff->buffer[cbuff->write], src, num_of_bytes);
	
	if(num_of_bytes > cbuff->capacity)
	{
		cbuff->write = num_of_bytes % cbuff->capacity;
	}
	cbuff->write = num_of_bytes + 1;
	
	
	return 0;
}

ssize_t CBuffRead(cbuff_t *cbuff, void *dest, size_t num_of_bytes)
{
	int st = -1;
	assert(cbuff);
	assert(dest);
	

	if(!CBuffIsEmpty(cbuff))
	{
		printf("!!!\n");
		memcpy(dest, &cbuff->buffer[cbuff->read], num_of_bytes);
		st = 0;
	}
	
	cbuff->read = num_of_bytes + 1;
	return st;
}

void CBuffDestroy(cbuff_t *cbuff)
{
	assert(cbuff);
	free(cbuff);
}

size_t CBuffCapacity(const cbuff_t *cbuff)
{
	assert(cbuff);
	return cbuff->capacity;
}


int CBuffIsEmpty(const cbuff_t *cbuff)
{
	assert(cbuff);
	return cbuff->read == cbuff->write;
}



static void buf_reset(cbuff_t *cbuff)
{
	assert(cbuff);
	cbuff->write = 0;
	cbuff->read = 0;
}


