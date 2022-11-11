#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


void Insert(stack_t *stack, int temp);

void Recursia(stack_t *stack)
{
	int temp = 0;

	
	if(!StackIsEmpty(stack))
	{
		temp =*(int *)StackPeek(stack);	
		StackPop(stack);
		Recursia(stack);
		Insert(stack, temp);
		
	}
}

void Insert(stack_t *stack, int temp)
{
	int top = 0;
	if(StackSize(stack) == 0)
	{
	
		StackPush(stack, &temp);
		return;
	}

	top = *(int *)StackPeek(stack);
	StackPop(stack);
	Insert(stack, temp);
	StackPush(stack, &top);
	
}

void Print(stack_t *stack)
{
	while(!StackIsEmpty(stack))
	{
		printf("%d\n", *(int *)StackPeek(stack));
		StackPop(stack);
	}
}

int main()
{
	stack_t *new_stack = StackCreate(4,3);
	int i = 0;
	int arr[] = {10, 20, 30};
	
	printf("------Test int------\n");
	for( ; i < 3; ++i)
	{
		StackPush(new_stack, &arr[i]);  
	}
	Print(new_stack);
	for(i = 0 ; i < 3; ++i)
	{
		StackPush(new_stack, &arr[i]);  
	}
	Recursia(new_stack);
	Print(new_stack);
	StackDestroy(new_stack);
	return 0;
}
