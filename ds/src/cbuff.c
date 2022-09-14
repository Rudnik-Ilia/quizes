/**********************
* Title : Worksheet 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/

#include <stdio.h>
#include <stddef.h> /* size_t*/
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h>

#include "utils.h"
#include "cbuff.h"



struct cbuff{
	
	#ifndef NDEBUG
	void *mine;
	#endif

	size_t capacity;
	size_t freespace;
	size_t read;
	size_t write;
	char buffer[1];

};
static int buf_reset(cbuff_t *cbuff);
static size_t check(size_t num, size_t free);

cbuff_t *CBuffCreate(size_t capacity)
{
	cbuff_t * new_cbuff = malloc(sizeof(cbuff_t) + capacity);
	if(NULL == new_cbuff)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	#ifndef NDEBUG
	new_cbuff->mine = DEAD;
	#endif
	
	new_cbuff->capacity = capacity;
	new_cbuff->freespace = capacity;
	buf_reset(new_cbuff);
	return new_cbuff;	

}

ssize_t CBuffWrite(cbuff_t *cbuff, const void *src, size_t num_of_bytes)
{
	size_t i = 0;
	assert(cbuff);
	assert(src);
	#ifndef NDEBUG
	if(cbuff->mine != DEAD)
	{
		return -1;
	}	
	#endif
	
	/*
	if(CBuffFreeSpace(cbuff) < num_of_bytes)
	{
		num_of_bytes = CBuffFreeSpace(cbuff);
	}
	
	*/
	
	i = check(num_of_bytes, CBuffFreeSpace(cbuff));
	memcpy(&cbuff->buffer[cbuff->write + 1], src, i);
	cbuff->write = (cbuff->write + i) % cbuff->capacity;
	cbuff->freespace = cbuff->freespace - i;
	
	return i;
}

ssize_t CBuffRead(cbuff_t *cbuff, void *dest, size_t num_of_bytes)
{
	
	assert(cbuff);
	assert(dest);
	
	#ifndef NDEBUG
	if(cbuff->mine != DEAD)
	{
		return -1;
	}	
	#endif
	
	if(!CBuffIsEmpty(cbuff))
	{
		memcpy(dest, &cbuff->buffer[cbuff->read + 1], num_of_bytes);
	}
	
	cbuff->read = (cbuff->read + num_of_bytes) % cbuff->capacity;
	cbuff->freespace = cbuff->freespace + num_of_bytes;
	
	return num_of_bytes;
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

size_t CBuffFreeSpace(const cbuff_t *cbuff)
{
	assert(cbuff);
	return cbuff->freespace;

}


static size_t check(size_t num, size_t free)
{
	return num > free ? free : num;
}


static int buf_reset(cbuff_t *cbuff)
{
	assert(cbuff);
	
	#ifndef NDEBUG
	if(cbuff->mine != DEAD)
	{
		return -1;
	}	
	#endif
	cbuff->write = 0;
	cbuff->read = 0;
	return 0;
}


