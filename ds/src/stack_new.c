/**********************
* Title : Worksheet 9
* Author: Anastasia Lurye
* Reviewer: Ira
* Date : 5.09.22
***********************/



#include <stdio.h> /* printf , perror */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "../include/stack.h"

struct stack
{
	size_t element_size;
	size_t capasity;
	size_t amount;
	void *stack_arr;
};


stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t)) ;
	stack -> stack_arr = malloc(element_size * num_of_elements);
	
	if (NULL == stack)
	{
		perror("Memory allocation error");
		return NULL;
	}

	stack -> element_size = element_size;
	stack -> capasity = num_of_elements;
	stack -> amount = 0;
	return stack;
}

void StackPush(stack_t *stack, const void *data)
{
	assert(stack);
	assert(data);
	memcpy((char*)stack->stack_arr + stack->element_size*stack->amount, data, stack->element_size);
	++stack->amount;
}

void *StackPeek(const stack_t *stack)
{
	assert(stack);
	return (char*)(stack->stack_arr) + stack->element_size*(stack->amount - 1);
}

size_t StackSize(const stack_t *stack)
{
	assert(stack);
	return stack-> amount;
}


void StackPop(stack_t *stack)
{
	assert(stack);
	--stack->amount;
	
}
void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack -> stack_arr);
	free(stack);	
}

size_t StackCapacity(const stack_t *stack)
{
	assert(stack);
	return stack -> capasity;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	return (stack->amount) ? 1 : 0;
}




