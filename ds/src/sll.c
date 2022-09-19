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

void SortedLLDestroy(sorted_list_t *list)
{
	 DLLDestroy(list->dll);
	 free(list);
	
}

sorted_list_iterator_t SortedLLInsert(sorted_list_t *list, void *data)
{	
	assert(NULL != data);
	

}





int SortedLLIsEqualIter(const sorted_list_iterator_t iter1, const sorted_list_iterator_t iter2)
{
	return DLLIsEqualIter(iter1.dll_iter, iter2.dll_iter);

}

int SortedLLIsEmpty(const sorted_list_t *list)
{
	return DLLBegin(list->dll) == DLLEnd(list->dll);
}

size_t SortedLLSize(const sorted_list_t *list)
{
	return DLLSize(list->dll);
}

void *SortedLLGetData(const sorted_list_iterator_t iter)
{
	return DLLGetData(iter.dll_iter);
}


sorted_list_iterator_t SortedLLBegin(const sorted_list_t *list)
{
	sorted_list_iterator_t iter;
	
	assert(NULL != list);
	
	iter.dll_iter = DLLBegin(list->dll);
	
	return iter;
}

sorted_list_iterator_t SortedLLEnd(const sorted_list_t *list)
{
	sorted_list_iterator_t iter;
	
	assert(NULL != list);
	
	iter.dll_iter = DLLEnd(list->dll);
	
	return iter;
}

sorted_list_iterator_t SortedLLNext(sorted_list_iterator_t iter)
{
	iter.dll_iter = DLLNext(iter.dll_iter); 
	return iter;
	
	
}
sorted_list_iterator_t SortedLLPrev(sorted_list_iterator_t iter)
{
	iter.dll_iter = DLLPrev(iter.dll_iter); 
	return iter;
}




