#pragma once
#ifndef __SLL_H__
#define __SLL_H__

typedef struct sll sll_t;

typedef struct node* iterator_t;

typedef int (*action_func)(void *data, void *param);
typedef int (*is_match_func)(const void *data, void *param);

/** Goes in source
 * typedef struct node node_t;
 *
 * struct sll
 * {
 *      node_t *head;
 *      node_t *tail;
 * };
 *
 * struct node
 * {
 *      void *data;
 *      struct node *next;
 * };
 */

sll_t *SllCreate(void);

void SllDestroy(sll_t *list);

/**
 * insert new node before iterator param
 * return iterator to new node
 * return dummy node on fail with magic num 0xDEADBEEF
 */
iterator_t SllInsert(iterator_t iter, void *data);

/**
 * O(1) and should never fail
 */
iterator_t SllRemove(iterator_t iter);

iterator_t SllFind(iterator_t from, iterator_t to, is_match_func is_match, void *param);


void SllSetData(iterator_t iter, void *data);

void *SllGetData(iterator_t iter);

size_t SllCount(const sll_t *list);

int SllIsEmpty(const sll_t *list);

iterator_t SllBegin(const sll_t *list);

iterator_t SllEnd(const sll_t *list);

iterator_t SllNext(iterator_t iter);

int SllIterIsEqual(iterator_t iter1, iterator_t iter2);

int SllForEach(iterator_t from, iterator_t to, 
        action_func func, void *param);
        
        
sll_t *SllAppend(sll_t *dest, sll_t *src);      




#endif
