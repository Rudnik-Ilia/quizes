
#include <stdlib.h> /*malloc*/
#include <assert.h> /**/
#include <stdio.h>


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

bst_node_t *CreateNode(bst_node_t *parent, bst_node_t *left, bst_node_t *right, void *data)
{
	bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	
	new_node->parent = parent;
	new_node->childrens[LEFT] = left; 
	new_node->childrens[RIGHT] = right;
	new_node->data = data;
	
	return new_node;
}



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
	
	return (bst_iter_t)&tree->root;;
}

void *BSTGetData(const bst_iter_t iter)
{
	return iter->data;
}

void BSTDestroy(bst_t *tree)
{
	free(tree->root.childrens[LEFT]);
	free(tree);
}

int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	return (NULL == tree->root.childrens[0]);

}

bst_iter_t BSTNext(const bst_iter_t iter)
{
	bst_iter_t runner = NULL;
	bst_iter_t parent = NULL;
	bst_iter_t result = NULL;

	runner = iter;
	if(runner->childrens[RIGHT] == NULL)
	{
		while(BSTIsSameIter(runner, runner->parent->childrens[RIGHT]))
		{
			runner = runner->parent;
		}
		result = runner->parent;	
	}
	else 
	{
		if(runner->childrens[RIGHT]->childrens[LEFT] == NULL)
		{
			return iter->childrens[RIGHT];
		}
		else
		{
			while(BSTIsSameIter(runner, runner->childrens[LEFT]->parent))
			{
				runner = runner->childrens[LEFT];
			}
			result = runner;
		}
	}
	return result;
}

int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2)
{
	return iter1 == iter2;	
}





















