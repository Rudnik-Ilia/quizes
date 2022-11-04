/**********************
* Title : Worksheet Recursion
* Author: Ilia Rudnik
* Reviewer: Victor
* Date : 4/11/2022
* Status : approved
***********************/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../../ds/include/stack.h"

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

size_t StrLen(const char *str)
{
	return *str ? 1 + StrLen(str+1) : 0;
}

int StrCmp(const char *s1, const char *s2)
{
	if (*s1 != '\0' && *s1 == *s2) 
	{
		return StrCmp(s1 + 1, s2 + 1);
	} 
	else 
	{
		return *s1 - *s2;
	}
}

char *StrCpy(char *dest, const char *src) 
{
	if ((*dest = *src) != '\0') 
	{
		return StrCpy(dest + 1, src + 1);
	} 
	else 
	{
		return dest;
	}
}

char *StrCat(char *dest, const char *src)
{
	StrCpy(dest + StrLen(dest), src);
	return dest;
}	


char *StrStr(const char *haystack, const char *needle)
{

	if (*haystack == '\0')
	{
		return NULL;
	}

	if (strncmp(haystack, needle, StrLen(needle)) == 0)
	{
		return (char*)haystack;
	}

	return StrStr(haystack + 1, needle);
}

static int GetElem(stack_t *stack)
{
	int res = *(int*)StackPeek(stack);
	StackPop(stack);
	return res;
}

void RecurseCompare(stack_t *stack, int curr)
{
	int head = 0;
	if (StackIsEmpty(stack) || curr >= *(int *)StackPeek(stack))
	{
		StackPush(stack, &curr);
		return;
	}
	head = GetElem(stack);
	RecurseCompare(stack, curr);
	StackPush(stack, &head);
}

void StackSort(stack_t *stack)
{
	int curr = 0;
	if (StackIsEmpty(stack))
	{
		return;
	}
	curr = GetElem(stack);
	StackSort(stack);
	RecurseCompare(stack, curr);
		
}






