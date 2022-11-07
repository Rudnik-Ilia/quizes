#include <stdlib.h>
#include <assert.h>

#include <stdio.h>
#include "../include/SLL.h"
#include "../include/stack.h"


typedef struct node
{
	void *data;
	struct node *next;
}node_t;

node_t *BornNode(void *data, void *next)
{
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	assert(data);
	
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	new_node->next = next;
	return new_node;
}

int FibonachiRecur(int n)
{
	if(1 == n|| 0 == n)
	{
		return n;
	}
	else
	{
		return FibonachiRecur(n-1) + FibonachiRecur(n-2);
	}
}

int FibonachiIter(int n)
{
	int pre = 1;
	int now = 1;
	int sum = 0;
	int i = 0;
	if(n <= 2)
	{
		now = 1;
	}
	for(i = 3; i <= n; ++i)
	{
		sum = pre + now;
		pre = now;
		now = sum;
	}
	return sum;
}


void Reverse(node_t *prev, node_t *cur)
{
   if(cur){
      Reverse(cur,cur->next);
      cur->next = prev;
    }
    else{
      cur = prev;
    }
}

int GetElem(stack_t *first)
{
	int res = *(int*)StackPeek(first);
	StackPop(first);
	return res;
}


void SortStack(stack_t *first)
{
	int tmp = 0;
	int res = 0;
	
	stack_t *second = StackCreate(4, 5);
	stack_t *third = StackCreate(4, 5);
	
	tmp = GetElem(first);	
}






int main()
{
	size_t i = 0;
	int arr[] = {4,1,3,2,5};
	
	stack_t * first = StackCreate(4, 5);
	
	for(i = 0; i < 5; ++i)
	{
		StackPush(first, &arr[i]);
	}
	
	printf("Size of stack: %ld\n",  StackSize(first)); 

	SortStack(first);
	


















	
/*
	printf("%d\n", FibonachiIter(8));
	printf("%d\n", FibonachiRecur(8));
	size_t i = 0;
	int arr[] = {1,2,3,4,5};
	
	node_t *item_1 = BornNode(&arr[4], NULL);
	node_t *item_2 = BornNode(&arr[3], item_1);
	node_t *item_3 = BornNode(&arr[2], item_2);
	node_t *item_4 = BornNode(&arr[1], item_3);
	node_t *item_5 = BornNode(&arr[0], item_4);
	
	printf("%p\n", item_5->next);
	printf("%p\n", item_4);
	
	Reverse(NULL, item_5);
	
	printf("%p\n", item_5->next);
	*/
	
	
	


return 0;
}
