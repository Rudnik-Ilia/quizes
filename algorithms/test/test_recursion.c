

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "../include/recursion.h"
#include "../include/test.h"


void Test_Fibonachi()
{
	size_t i = 0;
	size_t steps = 15;
	int fib_arr[] = {0 ,1 ,1 ,2 ,3 ,5 ,8 ,13 ,21 ,34 ,55 ,89 ,144 ,233 ,377};
	for(i = 0; i < steps; ++i)
	{
		TEST("FibRec", FibRec(i), fib_arr[i]);
		TEST("FibIter", FibIter(i), fib_arr[i]);	
	}
}

node_t *BornNode(void *data, void *next)
{
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	assert(data);
	
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->data = *(int*)data;
	new_node->next = next;
	return new_node;
}

void Test_Flip()
{
	size_t i = 0;
	int arr[] = {1,2,3,4,5};
	
	node_t *runner = NULL;
	
	
	node_t *item_1 = BornNode(&arr[4], NULL);
	node_t *item_2 = BornNode(&arr[3], item_1);
	node_t *item_3 = BornNode(&arr[2], item_2);
	node_t *item_4 = BornNode(&arr[1], item_3);
	node_t *item_5 = BornNode(&arr[0], item_4);
	
	runner = ListFlip(item_5);
	
	for(i = 5; i != 0; --i)
	{
		TEST("Test Flip", runner->data, (int)i);
		runner = runner->next;
	}
	free(item_1);
	free(item_2);
	free(item_3);
	free(item_4);
	free(item_5);
}

void Test_String()
{

	char dest[20] = {0};
	char FIO[13] = {0};
	
	TEST("Strlen" ,StrLen("ilia"), 4);
	TEST("Strlen" ,StrLen("rudnik"), 6);
	TEST("Strlen" ,StrLen("infinity"), 8);
	TEST("Strlen" ,StrLen("a"), 1);
	TEST("Strlen" ,StrLen("calculatorcalculator"), 20);
	
	TEST("Strcmp",StrCmp("ilia", "ilia"), 0);
	TEST("Strcmp",StrCmp("ilia", "ili"), 97);
	TEST("Strcmp",StrCmp("ilia", "lia"), -3);
	TEST("Strcmp",StrCmp("ilia", "iliaaaaa"), -97);
	TEST("Strcmp",StrCmp("ilia", " "), 73);
	
	StrCpy(dest, "ilia");
	TEST("Strcpy",StrCmp("ilia", dest), 0);
	StrCpy(dest, "rudnik");
	TEST("Strcpy",StrCmp("rudnik", dest), 0);
	StrCpy(dest, "a");
	TEST("Strcpy",StrCmp("b", dest), 1);
	StrCpy(dest, "ilia");
	TEST("Strcpy",StrCmp("ilia", dest), 0);
	StrCpy(dest, "xxxxxxxxxx");
	TEST("Strcpy",StrCmp("sssssssss", dest), -5);
	
	
	TEST("Strstr: ",StrCmp(StrStr("i live in Bat-Yam", "B"), "Bat-Yam"), 0);
	TEST("Strstr: ",StrCmp(StrStr("i live in Bat-Yam", "l"), "live in Bat-Yam"), 0);
	TEST("Strstr: ",StrCmp(StrStr("i live in Bat-Yam", "m"), "m"), 0);
	TEST("Strstr: ",StrCmp(StrStr("i live in Bat-Yam", "i"), "i live in Bat-Yam"), 0);
	
	StrCpy(FIO, "qwerty");
	StrCat(FIO, "qwerty");

	TEST("Testing StrCat", StrCmp(FIO, "qwertyqwerty"), 0);
}

int CheckGetElem(stack_t *stack)
{
	int res = *(int*)StackPeek(stack);
	StackPop(stack);
	return res;
}

void Test_Sort()
{	
	size_t i = 0;
	int arr[] = {4,1,18,2,-9};
	int res[] = {18,4,2,1,-9};
	
	
	stack_t * stack = StackCreate(sizeof(int), 5);
	
	for(i = 0; i < 5; ++i)
	{
		StackPush(stack, &arr[i]);
	}
	
	TEST("Size of stack: ",  StackSize(stack), 5); 
	
	
	StackSort(stack);
	TEST("Size of stack: ",  StackSize(stack), 5); 
	for(i = 0; i < 5; ++i)
	{
		TEST("loop",  CheckGetElem(stack), res[i]); 
	}
	TEST("Size of stack: ",  StackSize(stack), 0);
	
	StackDestroy(stack); 
}

int main()
{

	Test_String();
	Test_Flip();
	Test_Fibonachi();
	Test_Sort();
	
	PASS;
return 0;
}
