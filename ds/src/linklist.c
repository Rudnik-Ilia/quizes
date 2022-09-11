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

#include "../include/SLL.h"
#include "../include/MYHEAD.h"

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


sll_t *SllCreate(void)
{
    sll_t *MyList = (sll_t *)malloc(sizeof(sll_t));
	node_t *dummy_node = (node_t *)malloc(sizeof(node_t));
	
    if(NULL == MyList || NULL == dummy_node)
	{
		return NULL;
	}
	
	dummy_node->data = MyList;
	dummy_node->next = DEAD;
    MyList->head = dummy_node;
    MyList->tail = dummy_node; 
    
    return MyList;
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
	

}

iterator_t SllInsert(iterator_t iter, void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	assert(data);
	assert(iter);
	
	new_node->data = iter->data;
	new_node->next = iter->next;
	iter->next = new_node;
	iter->data = data;
	
	if(new_node->next == DEAD)
	{
		((sll_t*)(new_node->data))->tail = new_node; 
	}
	return iter;
}

iterator_t SllFind(iterator_t from, iterator_t to, is_match_func is_match, void *param)
{
	assert(param);
}

size_t SllCount(const sll_t *list)
{
	size_t count = 0;
	iterator_t ptr = list->head;
	while(ptr != list->tail)
	{	
		ptr = ptr->next;
		++count;
	}
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


/* is match */

int MatchParam(const void *data, void *param)
{
	

} 






/* returns one new node */
/*

node_t* SingleNode(void *data, node_t *next)
{	
	node_t *new_node = NULL;
	assert(next);
	assert(data);
	new_node = (node_t*)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		printf("error");
	}
	new_node->data;
	new_node->next;
	return new_node;
}
node_t* SingleNode( void *data, node_t *next);
*/

