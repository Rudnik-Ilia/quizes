/************************************************************/
/*Title: stack.c                                             
**Author: Ira                                              
** Date: 2022-09-03                                         
** Reviewer: Ilia                                         
** Review status:                                            
************************************************************/

#include <assert.h>
#include <stdlib.h> /*malloc, free*/
#include <stdio.h> /*NULL*/
#include <string.h> /*memcpy*/

#include "../include/stack.h"

typedef enum status_t {SUCCESS=0, STACKOVERFLOW=1, EMPTYSTACK=2, MALLOC_FAULT=3}
status;

struct stack
{
	size_t num_of_elements;
	size_t element_size;
	size_t top;
	void *data;
};


stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
	
	if(NULL == stack)
	{
		/*puts("malloc1 failed");*/
		free(stack);
		exit(MALLOC_FAULT);
	}
	
	stack -> data = malloc(element_size * num_of_elements);
		if(NULL == stack -> data)
	{
		/*puts("malloc2 failed");*/
		free(stack -> data);
		exit(MALLOC_FAULT);
	}
	
	stack -> top = 0;
	stack -> num_of_elements = num_of_elements;
	stack -> element_size = element_size;
	
	return stack;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack -> data);
	free(stack);
}


int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	
	if (0 == stack -> top)
	{
		return EMPTYSTACK;
	}
	return 1;
}


void StackPush(stack_t *stack, const void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	if (stack -> num_of_elements == stack -> top)
	{
		puts("StackOverflow");
		exit(STACKOVERFLOW);
	}
	memcpy(stack -> data, data, stack -> element_size);
	stack -> data = (char*)stack -> data + stack -> element_size;;
	stack -> top += 1;
}


void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	if (0 == StackIsEmpty(stack))
	{	
		puts("Stack is empty");
		/*exit(STACKUNDERFLOW);*/
	}
	stack -> data = (char*)stack -> data - stack -> element_size;
	stack -> top -= 1;
}


void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	if (0 == StackIsEmpty(stack))
	{	
		puts("Stack is Empty");
		return NULL;
	}
	return (char*)stack -> data - stack -> element_size;
}


size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return stack -> top;
}


size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return stack -> num_of_elements;
}





