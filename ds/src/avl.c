#include <stdlib.h>
#include <assert.h>
#include "utils.h"
#include "avl.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef enum children {LEFT, RIGHT, MAX_CHILDREN} child_t;

typedef struct avl_node avl_node_t;

struct avl_node 
{
    void *data;
    avl_node_t *children[MAX_CHILDREN];
    size_t height;
};

struct avl
{
    avl_node_t root;
    int (*cmp_func)(const void *data, const void *key_data);
};

avl_node_t *CreateNode(avl_node_t *left, avl_node_t *right, void *data)
{
	avl_node_t *node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if(NULL == node)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	
	node->data = data;
	node->children[LEFT] = left; 
	node->children[RIGHT] = right;
	node->height = 1;
	
	return node;
}


avl_t *AVLCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	avl_t *avl = NULL;

	assert(NULL != cmp_func);

	avl = (avl_t *)malloc(sizeof(avl_t));
	if(NULL == avl)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	avl->cmp_func = cmp_func;

	avl->root.children[LEFT] = NULL;
	avl->root.children[RIGHT] = NULL;
	
	avl->root.data = NULL;
	avl->root.height = 1;

	return avl;
}

void *AVLFind(const avl_t *tree, const void *key_data)
{
	

}

size_t AVLHeight(const avl_t *tree)
{
	assert(NULL != tree);
	return tree->root->children[LEFT]->height;
}

size_t GetHeight(avl_node_t *node)
{
	if (node == NULL)
	{
		return 0;
	}    
	return node->height;
}

void SetHeight(avl_node_t *node, size_t height)
{
	if (node == NULL)
	{
		return;
	}    
	node->height == height;
}

int GetBalance(avl_node_t *node)
{
	if (node == NULL)
	{
		return 0;
	}
	return GetHeight(node->left) - GetHeight(node->right);
}













