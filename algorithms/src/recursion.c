/**********************
* Title : Worksheet Recursion
* Author: Ilia Rudnik
* Reviewer: Victor
* Date : 4/11/2022
* Status : approved
***********************/

#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

typedef struct node
{
	int data;
	struct node *next;
	
} node_t;

int FibRec(int idx)
{
	if(1 == idx|| 0 == idx)
	{	
		
		return idx;
	}
	else
	{
		return FibRec(idx-1) + FibRec(idx-2);
	}
}

int FibIter(int idx)
{
	int pre = 1;
	int now = 1;
	int sum = 1;
	int i = 0;
	
	if(1 == idx || 0 == idx)
	{	
		
		return idx;
	}
	for(i = 3; i <= idx; ++i)
	{
		sum = pre + now;
		pre = now;
		now = sum;
	}
	return sum;
}

node_t *ListFlip(node_t *head)
{
	node_t *next = NULL;
	node_t *curr = head;

	if (NULL == head  || NULL == head->next)
	{
		return head;
	}
	next = curr->next;    
	head = ListFlip(next);
	next->next = curr;
	curr->next = NULL;

	return head;
}

/*

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
*/





