/**********************
* Title : Worksheet Cbuff
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
	size_t space;
	size_t read;
	size_t write;
	char buffer[1];

};


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
	new_cbuff->space = 0;
	new_cbuff->write = 0;
	new_cbuff->read = 0;
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
	
	for (i = 0; i < num_of_bytes && (cbuff->capacity > cbuff->space); ++i)
	{
		
		cbuff -> buffer [(cbuff->write + i) % (cbuff->capacity)] = *((char *)src + i);
			
		++cbuff->space;
	}
	cbuff->write = (cbuff->write + i) % cbuff->capacity;

	return i;
}

ssize_t CBuffRead(cbuff_t *cbuff, void *dest, size_t num_of_bytes)
{
	size_t i = 0;
	assert(cbuff);
	assert(dest);
	
	#ifndef NDEBUG
	if(cbuff->mine != DEAD)
	{
		return -1;
	}	
	#endif
	
	for (i = 0; i < num_of_bytes && cbuff->space > 0; ++i)
	{
		*((char *)dest + i) = cbuff -> buffer [(cbuff->read + i) % (cbuff->capacity)];	
		--cbuff->space;
	}
	cbuff->read = (cbuff->read + i) % cbuff->capacity;

	return i;
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
	return !cbuff->space;
}

size_t CBuffFreeSpace(const cbuff_t *cbuff)
{
	assert(cbuff);
	return cbuff->capacity - cbuff->space;

}

	/* old version
	
	if(CBuffFreeSpace(cbuff) < num_of_bytes)
	{
		num_of_bytes = CBuffFreeSpace(cbuff);
	}
	
	
	i = check(num_of_bytes, CBuffFreeSpace(cbuff));
	memcpy(&cbuff->buffer[cbuff->write + 1], src, i);
	cbuff->write = (cbuff->write + i) % cbuff->capacity;
	cbuff->freespace = cbuff->freespace - i;
	*/
	/* old version
	
	if(!CBuffIsEmpty(cbuff))
	{
		memcpy(dest, &cbuff->buffer[cbuff->read + 1], num_of_bytes);
	}
	
	cbuff->read = (cbuff->read + num_of_bytes) % cbuff->capacity;
	cbuff->freespace = cbuff->freespace + num_of_bytes;
	*/

