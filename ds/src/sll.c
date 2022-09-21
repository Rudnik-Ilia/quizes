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
	sorted_list_iterator_t tmp;
	assert(NULL != data);
	
	tmp = SortedLLBegin(list);

	
	for(; !SortedLLIsEqualIter(tmp, SortedLLEnd(list)) && (list->func(data, SortedLLGetData(tmp)) >= 0); tmp = SortedLLNext(tmp))
	{
	 /* empty body*/
	}
	
	#ifndef NDEBUG
	tmp.list = list;
	#endif
	
	tmp.dll_iter = DLLInsert(tmp.dll_iter, data);
	
	return tmp;
}

sorted_list_iterator_t SortedLLRemove(sorted_list_iterator_t iter)
{
	iter.dll_iter = DLLRemove(iter.dll_iter);
	return iter;
}

void *SortedLLPopFront(sorted_list_t *list)
{
	assert(NULL != list);
	
	return DLLPopFront(list->dll);
}
void *SortedLLPopBack(sorted_list_t *list)
{	
	assert(NULL != list);
	
	return DLLPopBack(list->dll);
}

int SortedLLForEach(const sorted_list_iterator_t from, const sorted_list_iterator_t to, int (*action_func)(void *data, void *params), void *params)
{
	assert(NULL != params);
	
	#ifndef NDEBUG
	assert(from.list == to.list);
	#endif


	return DLLForEach(from.dll_iter, to.dll_iter, action_func, params);
}


int SortedLLIsEqualIter(const sorted_list_iterator_t iter1, const sorted_list_iterator_t iter2)
{
	return DLLIsEqualIter(iter1.dll_iter, iter2.dll_iter);

}

int SortedLLIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);
	return DLLBegin(list->dll) == DLLEnd(list->dll);
}

size_t SortedLLSize(const sorted_list_t *list)
{
	assert(NULL != list);
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
	
	#ifndef NDEBUG
	iter.list = list;
	#endif

	
	iter.dll_iter = DLLBegin(list->dll);
	
	return iter;
}

sorted_list_iterator_t SortedLLEnd(const sorted_list_t *list)
{
	sorted_list_iterator_t iter;
	assert(NULL != list);
	
	#ifndef NDEBUG
	iter.list = list;
	#endif

	
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


sorted_list_iterator_t SortedLLFind(const sorted_list_t *list, const sorted_list_iterator_t from, const sorted_list_iterator_t to, const void *data)
{
	
	sorted_list_iterator_t tmp = from;
	
	assert(NULL != data);
	assert(NULL != list);
	
	#ifndef NDEBUG
	assert(list == to.list);
	assert(from.list == to.list);
	#endif


	for(;!SortedLLIsEqualIter(tmp, to) && !(list->func(data, SortedLLGetData(tmp)) == 0); tmp = SortedLLNext(tmp))
	{
	 /* empty body*/
	};
		
	return tmp;
}

sorted_list_iterator_t SortedLLFindIf(const sorted_list_iterator_t from, const sorted_list_iterator_t to, int (*is_match)(const void *data, void *params), void *params)
{
	sorted_list_iterator_t tmp = from;
	
	assert(NULL != params);
	
	#ifndef NDEBUG
	assert(from.list == to.list);
	#endif
	
	tmp.dll_iter = DLLFind(from.dll_iter, to.dll_iter, is_match, params);
	return tmp;

}

sorted_list_t *SortedLLMerge(sorted_list_t *dest, sorted_list_t *src)
{
	size_t count = 0;
	size_t size_src = SortedLLSize(src);
	sorted_list_iterator_t iter_dest = SortedLLBegin(dest);
	
	assert(NULL != dest);
	assert(NULL != src);
	
	while(count < size_src)
	{
		if(dest->func(SortedLLGetData(SortedLLBegin(src)) ,SortedLLGetData(iter_dest)) <= 0 )
		{	
			
			DLLSplice(SortedLLBegin(src).dll_iter, SortedLLNext(SortedLLBegin(src)).dll_iter, iter_dest.dll_iter);
			++count;	
		}
		else 
		{   
			iter_dest = SortedLLNext(iter_dest);
		}
	}
	return dest;
}
















