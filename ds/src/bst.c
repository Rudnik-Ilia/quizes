
#include <stdlib.h> /*malloc*/
#include <assert.h> /**/

#include "bst.h"

typedef struct bst_node bst_node_t;

typedef enum child_node_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_CHILD_NODES = 2
}child_node_pos_t;

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *childrens[NUM_CHILD_NODES];
	void *data;
};

struct bst
{
	struct bst_node root;
	int (*cmp_func)(const void *data, const void *key_data);
};

static bst_iter_t Next_and_Prev(const bst_iter_t iter, child_node_pos_t stub);
static child_node_pos_t WhichChild(bst_iter_t iter);
static child_node_pos_t CheckChild(bst_iter_t iter);
bst_node_t *CreateNode(bst_node_t *parent, bst_node_t *left, bst_node_t *right, void *data);



bst_t *BSTCreate(int (*cmp_func)(const void *data, const void *key_data))
{		
	
	bst_t * bst = (bst_t*)malloc(sizeof(bst_t));
	
	bst->cmp_func = cmp_func;
	
	bst->root.parent = NULL;
	bst->root.childrens[LEFT] = NULL;
	bst->root.childrens[RIGHT] = NULL;
	bst->root.data = NULL;
	
	return bst;	
}

bst_iter_t BSTInsert(bst_t *tree, void *data)
{	
	bst_iter_t iter = NULL;
	bst_iter_t new_node = NULL;
	bst_iter_t roots = NULL;
	child_node_pos_t side = LEFT;
	
	assert(NULL != tree);
	
	new_node = CreateNode(NULL, NULL, NULL, data);
	
	iter = tree->root.childrens[LEFT];
	roots = &tree->root;

	
	for(;iter != NULL; iter = iter->childrens[side])
	{
		
		roots = iter;
		
		if(tree->cmp_func(BSTGetData(iter), data) >0)
		{
			side = LEFT;
		}
		if(tree->cmp_func(BSTGetData(iter), data) < 0)
		{
			side = RIGHT;
		}
	}
	new_node->parent = roots;
	roots->childrens[side] = new_node;
	
	return new_node;
	
}	

bst_iter_t BSTBegin(const bst_t *tree)
{
	bst_iter_t iter = NULL;
	
	assert(NULL != tree);
	
	iter = (bst_iter_t)&tree->root;
	
	while(iter->childrens[LEFT] != NULL)
	{
		iter = iter->childrens[LEFT];
	}
	return iter;
}

bst_iter_t BSTEnd(const bst_t *tree)
{
	assert(NULL != tree);
	
	return (bst_iter_t)&tree->root;
}

void *BSTGetData(const bst_iter_t iter)
{
	return iter->data;
}


int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	return (NULL == tree->root.childrens[0]);
}


int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2)
{
	return iter1 == iter2;	
}

size_t BSTSize(const bst_t *tree)
{
	size_t count = 0;
	
	bst_iter_t iter = NULL;
	
	assert(NULL != tree);
	
	iter = BSTBegin(tree);
	
	while(!BSTIsSameIter(BSTEnd(tree), iter))
	{
		iter = BSTNext(iter);
		++count;
	}
	return count;
}


bst_iter_t BSTNext(const bst_iter_t iter)
{	
	assert(NULL != iter);
	return Next_and_Prev(iter, RIGHT);	
}

bst_iter_t BSTPrev(const bst_iter_t iter)
{	
	assert(NULL != iter);
	return Next_and_Prev(iter, LEFT);	
}

bst_iter_t BSTFind(const bst_t *tree, void *key_data)
{
	int res = 0;
	bst_iter_t iter = NULL;
	
	assert(NULL != tree);
	assert(NULL != key_data);
	
	
	iter = tree->root.childrens[LEFT];
	
	
	for(;iter != NULL && 0 != (res = tree->cmp_func(key_data, iter->data)); iter = iter->childrens[res > 0]);
	
	if(NULL == iter)
	{
		iter = BSTEnd(tree);
	}

	return iter;
}

int BSTForEach(bst_iter_t from, const bst_iter_t to, int (*action_func)(void *data, void *params), void *param)
{
	int result = 0;
	
	assert(NULL != param);
	assert(NULL != to);
	assert(NULL != from);
	
	for(;!BSTIsSameIter(from, to) & (result == 0); result = action_func(BSTGetData(from), param), from = BSTNext(from))
	{
		/*EMPTY BODY*/
	}
	return result;	
}

static bst_iter_t Next_and_Prev(const bst_iter_t iter, child_node_pos_t stub)
{
	bst_iter_t runner = NULL;
	bst_iter_t result = NULL;

	runner = iter;
	if(runner->childrens[stub] == NULL)
	{
		while(BSTIsSameIter(runner, runner->parent->childrens[stub]))
		{
			runner = runner->parent;
		}
		result = runner->parent;	
	}
	else 
	{
		runner = runner->childrens[stub];
		
        	while (NULL != runner->childrens[!stub])
        	{
            		runner = runner->childrens[!stub];
        	}
        	result = runner;
	}
	return result;
}

bst_iter_t BSTRemove(bst_iter_t iter)
{
	bst_iter_t parent = NULL;
	bst_iter_t next = NULL;
	bst_iter_t tmp = NULL;
	child_node_pos_t side_child = WhichChild(iter); 
	child_node_pos_t side_par = CheckChild(iter);
	
	parent = iter->parent;
	next = BSTNext(iter);
	
	if(NULL == iter->childrens[LEFT] && NULL == iter->childrens[RIGHT])
	{
		iter->parent->childrens[side_par] = NULL;
	}

	else if(NULL == iter->childrens[LEFT] || NULL == iter->childrens[RIGHT])
	{
		side_child = WhichChild(iter);
		parent->childrens[side_par] = iter->childrens[side_child];
		iter->childrens[side_child]->parent = parent;	
	}
	
	else
	{	
		parent->childrens[side_par] = next;
		next->parent = parent;
		
		if(iter->childrens[RIGHT] == next)
		{
			next->childrens[LEFT] = iter->childrens[LEFT];
			iter->childrens[LEFT]->parent = next;
		}
		
		else
		{
			next->childrens[LEFT] = iter->childrens[LEFT];
			iter->childrens[LEFT]->parent = next;
			
			for(tmp = next ; NULL != tmp->childrens[RIGHT]; tmp = tmp->childrens[RIGHT])
			{
				/*EMPTY BODY*/
			}
			
			iter->childrens[RIGHT]->parent = tmp;
			tmp->childrens[RIGHT] = iter->childrens[RIGHT];	
		}
	}
	
	free(iter);	
	return parent;
}

void BSTDestroy(bst_t *tree)
{
	bst_iter_t iter = NULL;
	bst_iter_t tmp = NULL;

	assert(NULL != tree);

	iter = BSTBegin(tree);

	while(!BSTIsSameIter(iter, BSTEnd(tree)))
	{
		tmp = iter;
		iter = BSTNext(iter);
		BSTRemove(tmp);
	}

	free(tree);


}

/*******************************************************************************************************************************/

static child_node_pos_t WhichChild(bst_iter_t iter)
{
	if(iter->childrens[LEFT] &&  NULL == iter->childrens[RIGHT])
	{
		return LEFT;
	}
	
	else
	{
		return RIGHT;
	}	
}

static child_node_pos_t CheckChild(bst_iter_t iter)
{
	if(iter->parent->childrens[LEFT] == iter)
	{
		return LEFT;
	}
	else
	{
		return RIGHT;
	}
}

bst_node_t *CreateNode(bst_node_t *parent, bst_node_t *left, bst_node_t *right, void *data)
{
	bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	
	new_node->parent = parent;
	new_node->childrens[LEFT] = left; 
	new_node->childrens[RIGHT] = right;
	new_node->data = data;
	
	return new_node;
}















