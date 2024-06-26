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

#define DEAD (node_t*) 0xDEADBEEF

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
	assert(NULL != param);
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
	iterator_t temp = iter -> next;
	assert(iter);
	if(iter-> next == DEAD)
	{
		return iter;
	}	
	
	iter -> data = (iter -> next)-> data;
	iter -> next = (iter -> next) -> next;
	
	if(iter -> next  == DEAD)
	{
		((sll_t *)(iter -> data))-> tail = iter;
	}
	
	free(temp);
	return iter;


}

void SllDestroy(sll_t *list)
{
	iterator_t iter = SllBegin(list);
	iterator_t temp = NULL;
	
	assert(NULL != list);
	
	while(iter != list->tail)
	{	
		temp = iter;
		iter = SllNext(iter);
		free(temp);
	}
	free(iter);
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
	
	assert(NULL != data);
	assert(NULL != iter);
	
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
	assert(NULL != param);
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_match);
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
	assert(NULL != list);
	SllForEach(SllBegin(list), SllEnd(list), PlusOne, &count);
	return count;
}


void *SllGetData(iterator_t iter)
{
	assert(NULL != iter);
	return iter->data;
}
void SllSetData(iterator_t iter, void *data)
{
	assert(NULL != data);
	iter->data = data;
}

iterator_t SllBegin(const sll_t *list)
{
	assert(NULL != list);
	return list->head;
}

iterator_t SllEnd(const sll_t *list)
{
	assert(NULL != list);
	return list->tail;
}
iterator_t SllNext(iterator_t iter)
{
	assert(NULL != iter);
	return iter->next;
}

int SllIsEmpty(const sll_t *list)
{
	assert(NULL != list);
	return SllBegin(list) == SllEnd(list);
}
int SllIterIsEqual(iterator_t iter1, iterator_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	return iter1 == iter2;
}

int SllForEach(iterator_t from, iterator_t to, action_func func, void *param)
{	
	int st = 0;
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != func);
	assert(NULL != param);
	while(DEAD != SllNext(from))
	{	
		func(from->data, param);
		from = SllNext(from);	
	}	
	return st;
}

sll_t *SllAppend(sll_t *dest, sll_t *src)
{	
	assert(NULL != dest);
	assert(NULL != src);

	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;				
	dest->tail = src->tail;
	dest->tail->data = dest;
	src->tail = src->head;
	src->head->data = src;
	src->head->next = DEAD;
	return dest;
}


