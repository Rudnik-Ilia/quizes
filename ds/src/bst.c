
#include <stdlib.h> /*malloc*/
#include <assert.h> /**/

#include "bst.h"


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

bst_iter_t CreateNode(bst_iter_t *parent, bst_iter_t *left, bst_iter_t *right, void *data)
{
	bst_iter_t new_node = (bst_iter_t)malloc(sizeof(bst_iter_t));
	
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
	
	bst->root = *CreateNode(NULL, NULL, NULL, NULL) ;
	
	return bst;	
}


bst_iter_t BSTInsert(bst_t *tree, void *data)
{
	

}


void *BSTGetData(const bst_iter_t iter)
{
	return iter->data;
}


























