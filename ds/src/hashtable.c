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
#define DEAD (void*)0xDEADBEEF

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
	iterator_t iter = NULL;
	pair_t *pair = NULL;
	
	assert(NULL != ht);
	assert(NULL != key);
	assert(NULL != value);
	
	pair = CreatePair(key, value);
	

	SllInsert(SllBegin(ht->ht_items[ht->hash_func(key)]), pair);
	
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
	size_t hash = 0;
	iterator_t iter = NULL;
	
	assert(NULL != ht);
	assert(NULL != key);
	
	hash = ht->hash_func(key);
	
	if(ht->ht_items[hash] == NULL)
	{
		return NULL;
	}
	else
	{
		
		for(iter = SllBegin(ht->ht_items[hash]); ht->is_match(key,(((pair_t*)SllGetData(iter))->key)) || SllNext(iter) != DEAD ;iter = SllNext(iter))
		{
			return ((pair_t*)SllGetData(iter))->value;
		}
		
	}
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


















