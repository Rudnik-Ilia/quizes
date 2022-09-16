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
	tmp = iter->next;
	assert(NULL != iter);
	
	
	iter->data = (iter->next)->data;
	iter->next = (iter->next)->next;
	
	if(DEAD == iter->next)
	{	
		printf("TAil\n");
		
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
	assert(list);
	return DLLRemove(DLLBegin(list));
}

void *DLLPopBack(dllist_t *list)
{	

	assert(list);
	
	DLLRemove(DLLEnd(list));
	return
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
	return iter->next;
}

dllist_iter_t DLLPrev(const dllist_iter_t iter)
{   
	assert(iter);
	if(iter->previous == CAFE)
	{	
		printf("cafe");
		return iter->previous;
	}
	return iter;
}

int DLLIsEmpty(const dllist_t *list)
{
	assert(list);
	return DLLBegin(list) == DLLEnd(list);
}


























/*

dllist_iter_t DLLPushBack(dllist_t *list, void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if(NULL == new_node)
	{	
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	assert(NULL != data);
	assert(NULL != list);
	
	new_node->data = data;
	new_node->next = DEAD;
	new_node->previous = list->tail;
	
	list->tail->next = new_node;
	list->tail = new_node;
	
	return DLLEnd(list);
}

dllist_iter_t DLLInsert(dllist_iter_t iter, void *data);


size_t DLLSize(const dllist_t *list)
{
	assert(list);
	size_t count;
	
	return count;
}


*/

