
#include <stdlib.h> /* for malloc / realloc*/
#include <string.h> /* for memcpy */
#include <assert.h> /* for assert*/

#include "vector.h"

static const int growth_factor = 2;

struct vector
{
	size_t element_size;
	size_t capacity;
	size_t size;
	void *elements;
};

vector_t *VectorCreate(size_t element_size, size_t capacity)
{
	vector_t *vector = NULL;
	
	vector = (vector_t *)malloc(sizeof(vector_t));
	if(NULL != vector)
	{
		vector->elements = (void *)(malloc(element_size * capacity));
		if(NULL != vector->elements)
		{	
			vector->capacity = capacity;
			vector->element_size = element_size;
			vector->size = 0;
		}
		else
		{
			free(vector);
			vector = NULL;
		}
	}

	return vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	free(vector->elements);
	free(vector);
}

int VectorPushBack(vector_t *vector, const void *data)
{
	void *new_pointer = NULL;
	
	assert(NULL != vector);
	assert(NULL != data);

	memcpy((char *)vector->elements + (vector->size * vector->element_size), data, vector->element_size);
	vector->size += 1;

	if(vector->size == vector->capacity)
	{
		new_pointer = (void *)realloc(vector->elements, vector->capacity * growth_factor * vector->element_size);
		if(NULL != new_pointer)
		{
			vector->elements = new_pointer;
			vector->capacity *= growth_factor;
		}
	}

	return vector->size < vector->capacity;
}

void VectorPopBack(vector_t *vector)
{
	void *new_pointer = NULL;
	
	assert(NULL != vector);
	
	vector->size -= 1;
	if(vector->size <= vector->capacity / (growth_factor * growth_factor))
	{
		new_pointer = (void *)realloc(vector->elements, (vector->capacity / growth_factor) * vector->element_size);
		if(NULL != new_pointer)
		{
			vector->elements = new_pointer;
			vector->capacity /= growth_factor;
		}
	}
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->size;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->capacity;
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->size == 0;
}

void VectorSetElement(vector_t *vector, size_t index, const void *data)
{
	assert(NULL != vector);
	assert(NULL != data);
	
	memcpy((char *)vector->elements + (index * vector->element_size), data, vector->element_size);
}

void *VectorGetAccessToElement(const vector_t *vector, size_t index)
{
	return (char *)vector->elements + (index * vector->element_size);
}

vector_t *VectorReserve(vector_t *vector, size_t new_capacity)
{
	void *new_pointer = NULL;
	
	assert(NULL != vector);
	
	new_pointer = (void *)realloc(vector->elements, new_capacity * vector->element_size);
	if(NULL != new_pointer)
	{
		vector->elements = new_pointer;
		vector->capacity = new_capacity;
	}
	else
	{
		return NULL;
	}
	
	return vector;
}	

vector_t *VectorShrink(vector_t *vector)
{
	void *new_pointer = NULL;
	
	assert(NULL != vector);
	
	new_pointer = (void *)realloc(vector->elements, vector->size * vector->element_size);
	if(NULL != new_pointer)
	{
		vector->elements = new_pointer;
		vector->capacity = vector->size;
	}
	else
	{
		return NULL;
	}
	
	return vector;
}
