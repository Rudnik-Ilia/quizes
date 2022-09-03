


#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand */
#include "../include/stack.h"





int main()
{
/*




	StackPop(IntStack);
	printf("%d\n", *(int*)StackPeek(IntStack));

	StackPush(IntStack, &c);
	StackPush(IntStack, &b);
	StackPush(IntStack, &a);
	int a = 10;
	int b = 20;
	int c = 30;
*/


	int i;
	int arr1[] = {10, 20, 30, 40, 50};
	
	stack_t* IntStack = StackCreate(4, 5);
	for(i = 0; i < 5; ++i)
	{ 	
		StackIsEmpty(IntStack);
		printf("%d\n", StackIsEmpty(IntStack));
		StackPush(IntStack, &arr1[i]);
		printf("%d\n", *(int*)StackPeek(IntStack));
	 	printf("%ld\n", StackSize(IntStack));
	};
	






return 0;
}


