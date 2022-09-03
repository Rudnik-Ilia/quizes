


#include <stdlib.h> /* malloc, free*/
#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */


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

 
stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
	stack_t * MyStack = (stack_t*)malloc(sizeof(stack_t));
	MyStack -> p_item = malloc(sizeof(element_size) * sizeof(num_of_elements));
	MyStack -> size = 0;
	MyStack -> item_size = sizeof(element_size);
	MyStack -> max_item = num_of_elements;
	return MyStack;
}


void StackDestroy(stack_t *stack)
{
	free(stack-> p_item);
	free(stack);
}


void StackPush(stack_t *stack, const void *data)
{
	memcpy((char*)(stack -> p_item) + stack->size * stack->item_size, data, stack->item_size);
	++stack->size;
}

void StackPop(stack_t *stack)
{
	++stack->size;	
}

void *StackPeek(const stack_t *stack)
{
	return (char*)(stack -> p_item) + stack->item_size*(stack->size-1);
}

size_t StackSize(const stack_t *stack)
{
	return stack->size;
}

int StackIsEmpty(const stack_t *stack)
{
		return stack->size ? 0 : 1;
}

size_t StackCapacity(const stack_t *stack)
{
	return stack->max_item;
}




















