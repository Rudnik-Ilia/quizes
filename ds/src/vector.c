#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand */
#include <string.h> /* memcpy*/
#include <assert.h> /* assert */


#include "../include/vector.h"

#define FACTOR 2


struct vector
{
	size_t max_item; 
	size_t size;
	size_t item_size;
	void  *p_item;
};



vector_t *VectorCreate(size_t element_size, size_t capacity)
{

	vector_t *MyVector = (vector_t*)malloc(sizeof(vector_t));
	if(NULL == MyVector)
	{
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
		return NULL;
	}
	MyVector -> p_item = malloc(element_size * capacity);
	if(NULL == MyVector->p_item)
	{
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
		free(MyVector);
		return NULL;              
	}
	MyVector -> size = 0;
	MyVector -> item_size = element_size;
	MyVector -> max_item = capacity;
	return MyVector;
}

void VectorDestroy(vector_t *vector)
{
	free(vector->p_item);
	free(vector);

}

int VectorPushBack(vector_t *vector, const void *data)
{
	
	void* p_new = NULL;
	int st = 1;
	
	assert(vector);
	assert(data);
	
	memcpy((char*)(vector -> p_item) + vector->size * vector->item_size, data, vector->item_size);
	++vector->size;
	
	if(vector->size == vector->max_item)
	{	
		p_new = realloc(vector->p_item, (vector->item_size*vector->max_item)*FACTOR);
		if(NULL != p_new)
		{
			vector->p_item = p_new;
			vector->max_item *= FACTOR;
			st = 1;
		}
		else
		{
			st = 0;
		}
	}
	return st;
	
}

void VectorPopBack(vector_t *vector)
{
	void* new;
	assert(vector);
	assert(0 != vector->size);
	
	--vector->size;
	if(vector->max_item > (float)vector->size / (FACTOR*FACTOR))
	{
		new = realloc(vector->p_item, vector->max_item*vector->item_size*FACTOR);
		if(NULL != new)
		{
			vector->p_item = new;
			vector->max_item /= FACTOR;
		}
	}
	if (vector->max_item == 0)
	{
		vector = VectorReserve(vector, 1);
	}

}
	
vector_t *VectorReserve(vector_t *vector, size_t new_capacity)
{
	void * new = NULL;
	assert(vector);
	if(new_capacity > vector->max_item)
	{
		new = realloc(vector->p_item, (vector->item_size*new_capacity));
		if(NULL != new)
		{
			vector->max_item = new_capacity;
			vector->p_item = new;
			return vector;
		}	
	}
	printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	return vector;
}

vector_t *VectorShrink(vector_t *vector)
{
	void* new;
	assert(vector);
	
	new = realloc(vector->p_item, vector->item_size*vector->size);
	
	if(NULL != new)
	{
		vector->p_item = new;
		vector->max_item = vector->size;
	}
	else
	{
		return NULL;
	}
	
	return vector;
}



void *VectorGetAccessToElement(const vector_t *vector, size_t index)
{	
	assert(index < vector->max_item);
	assert(vector);
	return (char*)(vector->p_item) + vector->item_size*index;
}

void VectorSetElement(vector_t *vector, size_t index, const void *data)
{		
	assert(index < vector->size);
	assert(data);
	assert(vector);
	memcpy((char*)(vector->p_item) + vector->item_size*index, data, vector->item_size);
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(vector);
	return (vector->size) ? 0: 1;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	return vector->max_item;
}
size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	return vector->size;
}





















