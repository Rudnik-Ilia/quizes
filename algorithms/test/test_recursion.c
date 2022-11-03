

#include <stdlib.h>
#include <assert.h>

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
}

int main()
{	
	printf("%ld\n",StrLen("ilia"));
/*
	head = item_5;
	head = item_5;
	
	printf("%d\n", item_5 - head);
	
	head = ListFlip(item_5);
	
	printf("%d\n", item_5 - head);
	TestListFlip();
	size_t i = 0;
	int arr[] = {4,1,3,2,5};
	
	stack_t * first = StackCreate(4, 5);
	
	for(i = 0; i < 5; ++i)
	{
		StackPush(first, &arr[i]);
	}
	
	printf("Size of stack: %ld\n",  StackSize(first)); 

	SortStack(first);
	Test_Flip();
	Test_Fibonachi();
	*/
	PASS;
return 0;
}
