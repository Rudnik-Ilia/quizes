/**********************
* Title : Worksheet DLL
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/

#include <stdlib.h> /* malloc */
#include <assert.h>
#include "dll.h"
#include "utils.h"

typedef struct dll_node node_t;

struct dll_node{

	void *data;
  	node_t *previous;
  	node_t *next;
  	
};
 
struct dllist{

	node_t *head;
	node_t *tail;	
};
 
node_t *BornNode(node_t *prev, node_t *next, void *data)
{	
	node_t *new_node = NULL;
	assert(prev);
	assert(next);
	assert(data);
	new_node = (node_t *)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		free(new_node);
		return NULL;
	}
	
	new_node->data = data;
	new_node->next = next;
	new_node->previous = prev;
	
	return new_node;
}



dllist_t *DLLCreate(void)
{
	node_t * dummy_node = NULL;
	dllist_t *myList = (dllist_t *)malloc(sizeof(dllist_t));
    if(NULL == myList)
    {
    	LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
    }
    dummy_node = BornNode(CAFE, DEAD, myList);
    if(NULL == dummy_node)
    {
    	LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
    }
    myList->head = dummy_node;
    myList->tail = dummy_node; 
    
    return myList;
}


dllist_iter_t DLLInsert(dllist_iter_t iter, void *data)
{
	node_t *new_node = NULL;
	assert(data);
	assert(iter);
	
	new_node = BornNode(iter, iter->next, iter->data);
	
	iter->data = data;
	iter->next = new_node;
	
	if(DEAD == iter->next->next)
	{	
		printf("TAil\n");
		((dllist_t*)(new_node->data))->tail = new_node; 
	}
	else
	{
		printf("head\n");
		iter->next->previous = new_node;
	}	
	return iter;
}




dllist_iter_t DLLPushFront(dllist_t *list, void *data)
{
	assert(list);
	assert(data);
	return DLLInsert(DLLBegin(list), data);
}

dllist_iter_t DLLPushBack(dllist_t *list, void *data)
{
	assert(list);
	assert(data);
	return DLLInsert(DLLEnd(list), data);;
}

dllist_iter_t DLLRemove(dllist_iter_t iter)
{
	node_t *tmp = NULL;
	assert(iter);
	
	if(DEAD == iter->next && CAFE != iter->previous)
	{
		iter = iter->previous;
	}
	
	tmp = iter->next;
	iter->data = (iter->next)->data;
	iter->next = (iter->next)->next;
	
	if(DEAD == iter->next)
	{	
		printf("tail\n");
		
		((dllist_t*)(iter->data))->tail = iter;
			 
	}
	else
	{
		printf("head\n");
		iter->next->previous = iter;	
	}
	
	free(tmp);
	return iter;
}


void *DLLPopFront(dllist_t *list)
{
	void * data = NULL;
	assert(list);
	data = DLLGetData(DLLBegin(list));
	DLLRemove(DLLBegin(list));
	return data;
}

void *DLLPopBack(dllist_t *list)
{	
	void * data = NULL;
	assert(list);
	data = DLLGetData(DLLEnd(list));
	DLLRemove(DLLEnd(list));
	return data;
	
}

void *DLLGetData(const dllist_iter_t iter)
{
	assert(iter);

	if(iter->next == DEAD)
	{
		return NULL;
	}
	return iter->data;
}
void DLLSetData(dllist_iter_t iter, void *data)
{
	assert(iter);
	if(iter->next != DEAD)
	{
		iter->data = data;
	}
}



dllist_iter_t DLLBegin(const dllist_t *list)
{
	assert(list);
	return list->head;

}
dllist_iter_t DLLEnd(const dllist_t *list)
{
	assert(list);
	return list->tail;
}

dllist_iter_t DLLNext(const dllist_iter_t iter)
{
	assert(iter);
	/*
	if(iter->next == DEAD)
	{	
		return iter;
	}
	*/
	return iter->next;
}

dllist_iter_t DLLPrev(const dllist_iter_t iter)
{   
	assert(iter);
	/*
	if(iter->previous == CAFE)
	{	
		return iter;
	}*/
	return iter->previous;
}


int DLLIsEmpty(const dllist_t *list)
{
	assert(list);
	return DLLBegin(list) == DLLEnd(list);
}



size_t DLLSize(const dllist_t *list)
{
	size_t count = 0;
	dllist_iter_t tmp = list->head;
	assert(list);
	for(; tmp != list->tail; tmp = tmp->next)
	{
		++count;
	} 
	return count;
}

int DLLIsEqualIter(const dllist_iter_t iter1, const dllist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	return (iter1 == iter2);
}


dllist_iter_t DLLFind(const dllist_iter_t from, const dllist_iter_t to, int (*is_match_func)(const void *data, void *params), void *param)
{
	dllist_iter_t tmp = from;
	assert(NULL != param);
	assert(NULL != from);
	assert(NULL != to);
	
	for(; !DLLIsEqualIter(from, to) || !is_match_func(tmp->data, param); tmp = tmp->next)
	{
		break;
	}	
	return tmp;

}
/*
int DLLForEach(const dllist_iter_t from, const dllist_iter_t to, int (*action_func)(void *data, void *params), void *param);
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
*/


	















