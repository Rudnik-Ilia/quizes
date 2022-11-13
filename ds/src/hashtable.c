/**********************
* Title : Worksheet DLL
* Author: Ilia Rudnik
* Reviewer: 
* Date : 06/09/2022
* Status : approved
***********************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "SLL.h"
#include "utils.h"

#define SHIFT sizeof(ht_t)


typedef struct pair
{
	const void *key;
	void *value;
}pair_t;

struct hash_table
{
	sll_t **ht_items;
	int (*is_match)(const void *key1, const void *key2);
	size_t (*hash_func)(const void *key);
	size_t size;
};

/**************************************************************/
static pair_t *CreatePair(const void *key, void* value);
static int FreeData(void *data, void *param);
/**************************************************************/


ht_t *HTCreate(size_t (*hash_func)(const void *key), size_t size, int (*is_match)(const void *key1, const void *key2))
{
	
	ht_t *ht = NULL;
	size_t i = 0;
	
	assert(NULL != hash_func);
	assert(NULL != is_match);
	
	ht = (ht_t*)malloc(sizeof(ht_t) + sizeof(sll_t*)*size);
	if(NULL == ht)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	ht->is_match = is_match;
	ht->hash_func = hash_func;
	ht->size = size;
	ht->ht_items = (sll_t**)((char*)ht + SHIFT);
	
	for(i = 0; i < size; ++i)
	{
		ht->ht_items[i] = SllCreate();
	}
	
	return ht;
}

int HTInsert(ht_t *ht, const void *key, void *value)
{
	pair_t *pair = NULL;
	iterator_t iter = NULL;
	size_t hash = 0;
	assert(NULL != ht);
	assert(NULL != key);
	assert(NULL != value);
	
	pair = CreatePair(key, value);
	
	hash = ht->hash_func(key);
	
	for(iter = SllBegin(ht->ht_items[hash]); iter != SllEnd(ht->ht_items[hash]); iter = SllNext(iter))
		{
			if(ht->is_match(((pair_t*)SllGetData(iter))->key, key))
			{
				FreeData(SllGetData(iter), NULL);
				SllSetData(iter, pair);
				return 0;

			}
		}
	SllInsert(SllEnd(ht->ht_items[ht->hash_func(key)]), pair);
	
	return 0;
}

void HTDestroy(ht_t *ht)
{
	size_t i = 0;
	void* param = NULL;
	
	assert(NULL != ht);
	
	param = ht;
	for(i = 0; i < ht->size; ++i)
	{
		SllForEach(SllBegin(ht->ht_items[i]), SllEnd(ht->ht_items[i]), FreeData, param);
		SllDestroy(ht->ht_items[i]);
	}
	free(ht);
}

size_t HTSize(const ht_t *ht)
{	
	size_t count = 0;
	size_t i = 0;
	
	assert(NULL != ht);
	
	for(i = 0; i < ht->size; ++i)
	{
		count += SllCount(ht->ht_items[i]);
	}
	return count;

}

int HTIsEmpty(const ht_t *ht)
{
	assert(NULL != ht);
	return !!HTSize(ht);
}

void *HTFind(const ht_t *ht, const void *key)
{
	iterator_t iter = NULL;
	
	size_t hash = ht->hash_func(key);
	
	assert(NULL != ht);
	assert(NULL != key);
	
	if(ht->ht_items[hash] == NULL)
	{
		return NULL;
	}
	
	else
	{
		for(iter = SllBegin(ht->ht_items[hash]); iter != SllEnd(ht->ht_items[hash]); iter = SllNext(iter))
		{
			if(ht->is_match(((pair_t*)SllGetData(iter))->key, key))
			{
				return ((pair_t*)SllGetData(iter))->value;
			}
		}
	}
	return NULL;
}




void HTRemove(ht_t *ht, const void *key)
{
	iterator_t iter = NULL;
	size_t hash = ht->hash_func(key);
	
	assert(NULL != ht);
	assert(NULL != key);
	
	for(iter = SllBegin(ht->ht_items[hash]);  iter != SllEnd(ht->ht_items[hash]); iter = SllNext(iter))
	{
		if(ht->is_match(key,(((pair_t*)SllGetData(iter))->key)))
		{
			  	FreeData(SllGetData(iter), NULL);
			  	SllRemove(iter);
			  	break;
		}
	}
	
}

int HTForEach(ht_t *ht, int (*action_func)(void *data, void *params), void *params)
{	
	size_t i = 0;
	iterator_t iter = NULL;
	int st = 0;
	
	assert(NULL != action_func);
	assert(NULL != ht);
	
	
 	for (i =0 ; i < ht->size && st == 0 ; ++i)
 	{
 		for(iter = SllBegin(ht->ht_items[i]); iter != SllEnd(ht->ht_items[i]); iter = SllNext(iter))
		{
			st = action_func(((pair_t*)SllGetData(iter))->value, params);
		}
 	}
 	return st;

}
 


/*****************************************************************************************************************************/




static pair_t *CreatePair(const void *key, void* value)
{
	pair_t *pair = NULL;
	
	assert(NULL != key);
	assert(NULL != value);
	
	pair = (pair_t*)malloc(sizeof(pair_t));
	if(NULL == pair)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	pair->key = key;
	pair->value = value;
	
	return pair;	
}

static int FreeData(void *data, void *param)
{
	(void)param;
	assert(NULL != data);
	
	free(data);
	
	return 0;
}


















