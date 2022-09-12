/**********************
* Title : Worksheet linklist
* Author: Ilia Rudnik
* Reviewer: Vadim
* Date : 06/09/2022
* Status : approved
***********************/

#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "SLL.h"
#include "utils.h"

#define DEAD (node_t*)0xDEADBEEF

typedef struct node node_t;

struct node {
    void *data;
    node_t *next;
};

struct sll {
    node_t *head;
    node_t *tail;
};

static int PlusOne(void *data, void *param)
{
	(void)data;
	assert(param);
	*(size_t*)param += 1;
	
	return 0;
}


sll_t *SllCreate(void)
{
    sll_t *myList = (sll_t *)malloc(sizeof(sll_t));
	node_t *dummy_node = (node_t *)malloc(sizeof(node_t));
	
    if(NULL == myList)
    {
    	LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
    }
    if(NULL == dummy_node)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(dummy_node);
		return NULL;
	}
	
	dummy_node->data = myList;
	dummy_node->next = DEAD;
    myList->head = dummy_node;
    myList->tail = dummy_node; 
    
    return myList;
}

iterator_t SllRemove(iterator_t iter)
{
	node_t *tmp = iter->next;
	assert(iter);
	if(DEAD == iter->next)
	{
		return iter;
	}
	
	iter->data = (iter->next)->data;
	iter->next = (iter->next)->next;
	
	if(DEAD == iter->next)
	{
		((sll_t*)(iter->data)) -> tail = iter;
	}
	
	free(tmp);
	return iter;
}

void SllDestroy(sll_t *list)
{
	iterator_t temp = list->head;
	assert(list);
	while(list->head != list->tail)
	{	
		list->head = list->head->next;
		free(temp);
		temp = list->head;
	}
	free(list->tail);
	free(list);
}

iterator_t SllInsert(iterator_t iter, void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if(NULL == new_node)
	{	
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	assert(data);
	assert(iter);
	
	new_node->data = iter->data;
	new_node->next = iter->next;
	iter->next = new_node;
	iter->data = data;
	
	if(DEAD == new_node->next)
	{
		((sll_t*)(new_node->data))->tail = new_node; 
	}
	return iter;
}

iterator_t SllFind(iterator_t from, iterator_t to, is_match_func is_match, void *param)
{
	assert(param);
	assert(from);
	assert(to);
	assert(is_match);
	while(!SllIterIsEqual(from, to) && !is_match(param, from->data))
	{
		from = SllNext(from);
		return from;	
	}
	return NULL;
}


size_t SllCount(const sll_t *list)
{
	size_t count = 0;
	assert(list);
	SllForEach(SllBegin(list), SllEnd(list), PlusOne, &count);
	return count;
}


void *SllGetData(iterator_t iter)
{
	assert(iter);
	return iter->data;
}
void SllSetData(iterator_t iter, void *data)
{
	assert(data);
	iter->data = data;
}

iterator_t SllBegin(const sll_t *list)
{
	assert(list);
	return list->head;
}

iterator_t SllEnd(const sll_t *list)
{
	assert(list);
	return list->tail;
}
iterator_t SllNext(iterator_t iter)
{
	assert(iter);
	return iter->next;
}

int SllIsEmpty(const sll_t *list)
{
	assert(list);
	return SllBegin(list) == SllEnd(list);
}
int SllIterIsEqual(iterator_t iter1, iterator_t iter2)
{
	assert(iter1);
	assert(iter2);
	return iter1 == iter2;
}

int SllForEach(iterator_t from, iterator_t to, action_func func, void *param)
{	
	int st = 0;
	assert(from);
	assert(to);
	assert(func);
	assert(param);
	while(DEAD != SllNext(from))
	{	
		func(from->data, param);
		from = SllNext(from);	
	}	
	return st;
}

sll_t *SllAppend(sll_t *dest, sll_t *src)
{	
	assert(dest);
	assert(src);

	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;				
	dest->tail = src->tail;
	dest->tail->data = dest;
	src->tail = src->head;
	src->head->data = src;
	src->head->next = DEAD;
	return dest;
}


