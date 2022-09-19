/**********************
* Title : Worksheet SLL
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/

#include <stdlib.h> /* malloc */
#include <assert.h>
#include "srtll.h"
#include "utils.h"

typedef struct sll_node node_t;

/*
struct sorted_list_iterator
{
	#ifndef NDEBUG
	sorted_list_t *list;
	#endif
	
	dllist_iter_t dll_iter;
};
*/

struct sorted_list{

	node_t *head;
	node_t *tail;	
};


struct sll_node{

	void *data;
  	node_t *next;	
};

/**************************************************************/
node_t *BornNode(void *data, node_t *next);
/***************************************************************/



sorted_list_t *SortedLLCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	assert(cmp_func);
		
	

}


node_t *BornNode(void *data, node_t *next)
{	
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	assert(next);
	assert(data); 
	if(NULL == new_node)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	new_node->data = data;
	new_node->next = next;
	
	return new_node;
}

