
/**********************
* Title : Worksheet 8,5 
* Author: Ilia Rudnik
* Reviewer: NASTya
* Date : 04/09/2022
* Status : 
***********************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand */

#include "../include/stack.h"

void Test_Integer();
void Test_Float();
void Test_Char();


int main()
{

	Test_Integer();	
	Test_Float();
	Test_Char();

return 0;
}


void Test_Integer()
{	
	int i;
	int arr1[] = {10, 20, 30, 40, 50};
	stack_t* IntStack = StackCreate(4, 5);
	printf("Test for Stack of integer\n");
	for(i = 0; i < 5; ++i)
	{ 	
		StackPush(IntStack, &arr1[i]);
		printf("ITEM: %d\n", *(int*)StackPeek(IntStack));
		printf("SIZE: %ld\n", StackSize(IntStack));
	};
	
	if(*(int*)StackPeek(IntStack) == 50 && StackSize(IntStack) == 5)
	{
		puts("PASS");
	} 
	else
	{
		printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	
	StackPop(IntStack);
	
	if(*(int*)StackPeek(IntStack) == 40 && StackSize(IntStack) == 4)
	{
		puts("PASS");
	} 
	else
	{
		printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	printf("=====================================================================\n");
	StackDestroy(IntStack);
	
}

void Test_Float()
{	
	int i;
	float arr1[] = {1.1, 2.2, 3.3, 4.4, 5.5};
	stack_t* FloatStack = StackCreate(4, 5);
	printf("Test for Stack of float\n");
	for(i = 0; i < 5; ++i)
	{ 	
		StackPush(FloatStack, &arr1[i]);
		printf("ITEM: %f\n", *(float*)StackPeek(FloatStack));
		printf("SIZE: %ld\n", StackSize(FloatStack));
	};	
	if(*(float*)StackPeek(FloatStack) == arr1[4] && StackSize(FloatStack) == 5)
	{
		puts("PASS");
	} 
	else
	{
		printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	
	StackPop(FloatStack);
	
	if(*(float*)StackPeek(FloatStack) == arr1[3] && StackSize(FloatStack) == 4)
	{
		puts("PASS");
	} 
	else
	{
		printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);

	}
	printf("=====================================================================\n");
	StackDestroy(FloatStack);
}

void Test_Char()
{	
	int i;
	char arr1[] = {'a', 'b', 'c', 'c', 'd'};
	stack_t* IntStack = StackCreate(1, 5);
	printf("Test for Stack of float\n");
	for(i = 0; i < 5; ++i)
	{ 	
		StackPush(IntStack, &arr1[i]);
		printf("ITEM: %c\n", *(char*)StackPeek(IntStack));
		printf("SIZE: %ld\n", StackSize(IntStack));
	};	
	if(*(char*)StackPeek(IntStack) == arr1[4] && StackSize(IntStack) == 5)
	{
		puts("PASS");
	} 
	else
	{
		printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	
	StackPop(IntStack);
	
	if(*(char*)StackPeek(IntStack) == arr1[3] && StackSize(IntStack) == 4)
	{
		puts("PASS");
	} 
	else
	{
		printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);

	}
	printf("=====================================================================\n");
	StackDestroy(IntStack);
	
}












