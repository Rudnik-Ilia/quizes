


#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand */


#include "../include/stack.h"

void Test_Integer()
{

	int i;
	int a = 60;
	int arr1[] = {10, 20, 30, 40, 50};
	stack_t* IntStack = StackCreate(4, 5);
	for(i = 0; i < 5; ++i)
	{ 	
		StackPush(IntStack, &arr1[i]);
		printf("%d\n", *(int*)StackPeek(IntStack));
		printf("%ld\n", StackSize(IntStack));
	};
	StackPush(IntStack, &a);
	StackPush(IntStack, &a);
	StackPush(IntStack, &a);
	printf("%d\n", *(int*)StackPeek(IntStack));
	
	if(*(int*)StackPeek(IntStack) == 50 && StackSize(IntStack) == 5)
	{
		puts("PASS");
	} 
	else
	{
		printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	
		

}




int main()
{
/*
	StackPop(IntStack);

		StackPush(IntStack, &arr1[i]);
	printf("%d\n", *(int*)StackPeek(IntStack));

	StackPush(IntStack, &b);
	StackPush(IntStack, &a);
	int a = 10;
	int b = 20;
	int c = 30;
		printf("%d\n", *(int*)StackPeek(IntStack));
		printf("%d\n", StackIsEmpty(IntStack));
		StackIsEmpty(IntStack);
	StackDestroy(IntStack);
	int i = 10;
	int a = 20;
	
	
	stack_t* IntStack = StackCreate(4, 5);
	printf("%d\n", *(int*)StackPeek(IntStack));
	StackPush(IntStack, &i);
*/
	Test_Integer();
	
	

	
	
	
	



return 0;
}


