/**********************
* Title : Worksheet DLL
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/

#include <stdlib.h> /* malloc */
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
 

dllist_t *DLLCreate(void)
{
	dllist_t *myList = (dllist_t *)malloc(sizeof(dllist_t));
	
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
	dummy_node->previous = DEAD;
    myList->head = dummy_node;
    myList->tail = dummy_node; 
    
    return myList;

}




