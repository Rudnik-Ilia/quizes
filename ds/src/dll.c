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

/**********************************************************************************************/
static int One(void *data, void *param);
node_t *BornNode(void *data, node_t *next, node_t *prev);

/**********************************************************************************************/
 


/********************** CREATE AND DECREATE FUNCTIONS****************************************************/
dllist_t *DLLCreate(void)
{		
	dllist_t *dll = (dllist_t *)malloc(sizeof(dllist_t));

	if(NULL == dll)
	{

		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}

	dll -> head = BornNode(dll, DEAD, DEAD);
	if(NULL == dll -> head)
	{
		free(dll);
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}

	dll -> tail = BornNode(dll, DEAD, dll->head);
	if(NULL == dll -> tail)
	{
		free(dll);
		free(dll -> head);
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}


	dll -> head -> next = dll -> tail;
	return dll;
}

void DLLDestroy(dllist_t *list)
{
	dllist_iter_t temp = NULL;

	assert(NULL != list);

	while (list->head != list->tail)
	{
		temp = list->head;
		list->head = DLLNext(temp);
		free(temp);
	}
	free(list->tail);
	free(list);
}

/********************** ADD AND INSERT FUNCTIONS****************************************************/
dllist_iter_t DLLInsert(dllist_iter_t iter, void *data)
{
	node_t *new_node = NULL;
	assert(data);
	assert(iter);
	
	new_node = BornNode(data, iter, iter->previous);
	
	if(new_node == NULL)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	iter->previous->next = new_node;
	iter->previous = new_node;	
	return new_node;
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
	
		((dllist_t*)(iter->data))->tail = iter;		 
	}
	else
	{
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
	data = DLLGetData(DLLEnd(list)->previous);
	DLLRemove(DLLEnd(list)->previous);
	return data;
	
}

/********************** GET & SET FUNCTIONS****************************************************/

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

/********************** ITERATOR FUNCTIONS****************************************************/

dllist_iter_t DLLBegin(const dllist_t *list)
{
	assert(list);
	return list->head->next;

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

int DLLIsEqualIter(const dllist_iter_t iter1, const dllist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	return (iter1 == iter2);
}

/********************** UTILS FUNCTIONS****************************************************/
int DLLIsEmpty(const dllist_t *list)
{
	assert(list);
	return DLLBegin(list) == DLLEnd(list);
}


size_t DLLSize(const dllist_t *list)
{
	size_t count = 0;
	assert(list);
	DLLForEach(DLLBegin(list), DLLEnd(list), &One, &count);
	return count;
}

int DLLForEach(const dllist_iter_t from, const dllist_iter_t to, int (*action_func)(void *data, void *params), void *param)
{	
	int st = 0;
	dllist_iter_t tmp = from;
	assert(from);
	assert(to);
	assert(action_func);
	assert(param);
	while(DEAD != tmp->next)
	{	
		if(action_func(tmp->data, param))
		{
			st = 0;
		}
		tmp = tmp->next;	
	}	
	return st;
}

/********************** FIND FUNCTIONS****************************************************/
dllist_iter_t DLLFind(const dllist_iter_t from, const dllist_iter_t to, int (*is_match_func)(const void *data, void *params), void *param)
{
	dllist_iter_t tmp = from;
	assert(param);
	assert(from);
	assert(to);
	
	for(; !DLLIsEqualIter(tmp, to) && !is_match_func(tmp->data, param); tmp = tmp->next)
	{
		/*EMPTY BODY*/
	}	
	return tmp;
}


int DLLMultiFind(const dllist_iter_t from, const dllist_iter_t to, int (*is_match_func)(const void *data, void *params), void *param, dllist_t *output_list)
{
	dllist_iter_t tmp = from;
	size_t count = 0;
	assert(param);
	assert(from);
	assert(to);
	while(!DLLIsEqualIter(tmp, to))
	{
		if(is_match_func(tmp->data, param))
		{
			DLLPushBack(output_list, tmp->data);
			++count;
		}
		tmp = tmp->next;
	}	
	return count;
}


void DLLSplice(dllist_iter_t from, dllist_iter_t to, dllist_iter_t dest)
{
	
	dllist_iter_t from_prev = NULL;
	dllist_iter_t to_prev = to->previous;

	assert(from);
	assert(to);
	assert(dest);
		
	from_prev = from->previous;																						
	from_prev->next = to;
	
	to->previous->next = dest;
	to->previous= from->previous;
	
	from->previous = dest->previous;
	
	dest->previous->next = from;
	dest->previous = to_prev; 
}



/********************** HELP FUNCTIONS****************************************************/
static int One(void *data, void *param)
{
	(void)data;
	assert(param);
	*(size_t*)param += 1;
	return 0;
}

node_t *BornNode(void *data, node_t *next, node_t *prev)
{	
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	assert(prev);
	assert(next);
	assert(data); 
	if(NULL == new_node)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	new_node->data = data;
	new_node->next = next;
	new_node->previous = prev;
	
	return new_node;
}


/*****OLD FUCTIONS*********/


/*

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
*/












