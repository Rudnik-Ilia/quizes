
/**********************
* Title : Worksheet stack 
* Author: Ilia Rudnik
* Reviewer: NASTya
* Date : 04/09/2022
* Status : aproved
***********************/

#include <stdlib.h> /* malloc, free*/
#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include "../include/stack.h"

/* need to delete printf*/
struct stack
{
	size_t element_size;
	size_t nmemb;
	size_t size;
};

stack_t *StackCreate(size_t element_size, size_t num_of_element)
{
	void *MyStack = malloc(sizeof(stack_t) + element_size * num_of_element);
	
	if(NULL == MyStack)
	{
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);              
	}

	((stack_t*)MyStack)->element_size = element_size;
	((stack_t*)MyStack)->nmemb = num_of_element;
	((stack_t*)MyStack)->size = 0;

	return MyStack;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack);
}

void StackPush(stack_t *stack, const void *data)
{
	assert(stack);
	assert(data);
	if(stack->size == stack->nmemb)
	{
		printf("SORRY, SIZE OF STACK WAS EXEEDED. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}

	memcpy((char*)stack + sizeof(stack_t) + stack->size * stack->element_size,
			data, stack->element_size);
	++stack->size;
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(stack->size != 0);
	--stack->size;
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	return (char*)stack + sizeof(stack_t) + (stack->size - 1) * stack->element_size;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	return !stack->size;
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->size;
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->nmemb;
}


/*
typedef union u {
  char bytes [sizeof(double)];
  double value;
} u;
 
int main () {
  u u1;
  u1.value = 234.23;
  char* p = &u1.bytes[4]; 
}
*/












