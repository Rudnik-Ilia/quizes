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
		printf("error");
	}
	
	dummy_node->data = MyList;
	dummy_node->next = DEAD;
    MyList->head = dummy_node;
    MyList->tail = dummy_node; 
    
    return MyList;
}

void SllDestroy(sll_t *list)
{
	

}

iterator_t SllInsert(iterator_t iter, void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if(NULL == new_node)
	{
		printf("error");
	}
	
	assert(data);
	assert(iter);
	
	new_node->data = iter->data;
	new_node->next = iter->next;
	iter->next = iter;
	iter->data = data;
	
	if(new_node->next == DEAD)
	{
		((sll_t*)(new_node->data))->tail = new_node; 
	}
	return iter;
}

void *SllGetData(iterator_t iter)
{
	assert(iter);
	return iter->data;
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

