/**********************
* Title : Worksheet SLL
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/


#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "srtll.h"
#include "utils.h"
#include "dll.h"

typedef int (*cmp_func_t)(const void *data1, const void *data2);
typedef struct sll_node node_t;

struct  sorted_list 
{
	dllist_t *dll;
	cmp_func_t func;
};

sorted_list_t *SortedLLCreate(cmp_func_t func_cmp)
{
	sorted_list_t *srtll = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if(NULL == srtll)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	} 
	srtll -> dll = DLLCreate();
	srtll -> func = func_cmp;
	
	return srtll;
}






