/**********************
* Title : Vector
* Author: Anastasia Lurye
* Reviewer: Alena
* Date : 6.09.22
***********************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <stdio.h>  /* printf */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include "../include/vector.h"

#define FactorGrowth 2

struct vector
{
	size_t capacity;
	size_t size;
	size_t amount;
	void *pt_components;	
};

vector_t *VectorCreate(size_t element_size, size_t capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	vector -> pt_components = malloc(element_size * capacity);
	vector -> size = element_size;
	vector -> capacity = capacity;
	vector -> amount = 0; 
	return vector;
}

int VectorPushBack(vector_t *vector, const void *data)
{
	int status = 1;
	assert(vector);
	assert(data);
	
	memcpy((char*)vector -> pt_components + vector -> amount * vector -> size, data, vector -> size);
	++vector -> amount;
	if(vector -> amount == vector -> capacity)
	{
		void *ptr = NULL;
		ptr = realloc(vector -> pt_components, vector -> capacity * vector -> size * FactorGrowth);
		if(ptr == NULL)
		{
			return 0;
		}
		vector -> pt_components = ptr;
		vector -> capacity = vector -> capacity * FactorGrowth;
	
	}
	return status;
}

void *VectorGetAccessToElement(const vector_t *vector, size_t index)
{
	return (char *)vector -> pt_components +  index * vector -> size;
}

vector_t *VectorShrink(vector_t *vector)
{
	void* ptr = NULL;
	assert(vector);
	
	if(vector -> capacity > vector -> size)
	{
		ptr = realloc(vector -> pt_components, vector -> amount * vector -> size);
		vector -> pt_components = ptr;
		vector -> capacity = vector -> size;
	}
	return vector;	
}

void VectorPopBack(vector_t *vector)
{
	assert(vector);
	--vector -> amount;
	VectorShrink(vector);
}

size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	return vector -> amount;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	return vector -> capacity;
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(vector);
	return !vector->amount;
}

void VectorSetElement(vector_t *vector, size_t index, const void *data)
{
	assert(vector);
	assert(data);
	assert(index < vector -> amount);
	memcpy((char*)vector -> pt_components + vector -> size * index, data, vector -> size);
}

vector_t *VectorReserve(vector_t *vector, size_t new_capacity)
{
	void *ptr = NULL;
	
	if(new_capacity > vector -> capacity)
	{
		ptr = realloc(vector -> pt_components, new_capacity * vector -> size);	
		vector -> pt_components = ptr; 
	    vector -> capacity = new_capacity;
	    return vector;
		
	}
	return vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(vector);
	free(vector-> pt_components);
	free(vector);
}


