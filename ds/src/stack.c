
#include <stdlib.h> /* malloc, free*/
#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

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



typedef struct
{
	size_t max_item; 
	size_t size;
	size_t item_size;
	void  *p_item;
} stack_t;

 /*

void StackPush(stack_t *stack, const void *data)
{
	memcpy((char*)(stack -> p_item) + stack->size * stack->item_size, data, stack->item_size);
	++stack->size;
}


stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
	void *place = (void*)malloc(sizeof(stack_t) + sizeof(element_size) * sizeof(num_of_elements));
	stack_t* MyStack = (stack_t*)((char*)place);
	MyStack -> p_item = (void*)((char*)MyStack + sizeof(MyStack));
	MyStack -> size = 0;
	MyStack -> item_size = sizeof(element_size);
	MyStack -> max_item = num_of_elements;
	return MyStack;
}
*/

stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
	stack_t *MyStack = (stack_t*)malloc(sizeof(stack_t));
	if(NULL == MyStack)
	{
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	MyStack -> p_item = malloc(sizeof(element_size) * sizeof(num_of_elements));
	if(NULL == MyStack->p_item)
	{
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);              
	}
	MyStack -> size = 0;
	MyStack -> item_size = sizeof(element_size);
	MyStack -> max_item = num_of_elements;
	return MyStack;
}


void StackDestroy(stack_t *stack)
{
	assert(stack);
	free(stack-> p_item);
	free(stack);
}

void StackPush(stack_t *stack, const void *data)
{
	assert(stack);
	assert(data);
	if(stack->size == stack->max_item)
	{
		printf("SORRY, SIZE OF STACK WAS EXEEDED. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	memcpy((char*)(stack -> p_item) + stack->size * stack->item_size, data, stack->item_size);
	++stack->size;
}


void StackPop(stack_t *stack)
{	
	assert(stack);
	--stack->size;	
}

void *StackPeek(const stack_t *stack)
{
	assert(stack);
	return (char*)(stack -> p_item) + stack->item_size*(stack->size-1);
}

size_t StackSize(const stack_t *stack)
{
	assert(stack);
	return stack->size;
}

int StackIsEmpty(const stack_t *stack)
{	
	assert(stack);
	return stack->size ? 0 : 1;
}

size_t StackCapacity(const stack_t *stack)
{
	if(NULL == stack)
	{
		return 0;
	}
	return stack->max_item;
}




















