
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
	bst_iter_t *parent;
	bst_iter_t *childrens[NUM_CHILD_NODES];
	void *data;
};

struct bst
{
	struct bst_node root;
	int (*cmp_func)(const void *data, const void *key_data);
};

bst_node_t CreateNode(bst_node_t *parent, bst_node_t *left, bst_node_t *right, void *data)
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
	bst_node_t dummy = NULL;
	bst_t * bst = (bst_t*)malloc(sizeof(bst_t));
	
	bst->cmp_func = cmp_func;
	/*
	bst->root.parent = NULL;
	bst->root.childrens[LEFT] = NULL;
	bst->root.childrens[RIGHT] = NULL;
	bst->root.data = NULL;
	*/
	bst->root = dummy;
	
	return bst;	
}

/*
bst_iter_t BSTInsert(bst_t *tree, void *data)
{	
	assert(NULL != tree);
	  
	bst_iter_t iter = tree -> root;
	
	bst_iter_t new_node = CreateNode(iter, NULL, NULL, data);

	if (iter->childrens[LEFT] == NULL)
	{
		iter->childrens[LEFT] = new_node;
	}

	else 
	{
		iter = Next(iter);
	}

	while (iter != NULL)
	{
		cmp(iter->data, key_data) > 0 - > iter = iter -> right 
		cmp(iter->data, key_data) < 0 - > iter = iter -> left
	}
	


*/

bst_iter_t BSTNext(const bst_iter_t iter)
{
	return *iter->childrens[RIGHT];
}

bst_iter_t BSTPrev(const bst_iter_t iter)
{
	return *iter->childrens[LEFT];
}

void *BSTGetData(const bst_iter_t iter)
{
	return iter->data;
}

void BSTDestroy(bst_t *tree)
{
	free(tree->root);
	free(tree);
}
























