#include <stdlib.h>
#include <assert.h>
#include "utils.h"
#include "avl.h"

#define COUNT 10


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

void *AVLInsert_Ax(avl_t *tree, void *data, avl_node_t *node, avl_node_t *new);
void *GetData(avl_node_t *node);
void Destroy_Ax(avl_node_t *node);
size_t GetHeight(avl_node_t *node);
avl_node_t *CreateNode(void *data);
void *Find_Ax(const avl_t *tree, avl_node_t *node, const void *key_data);


static void Print2D(avl_node_t *root, int space);

avl_node_t *CreateNode(void *data)
{
	avl_node_t *node = malloc(sizeof(avl_node_t));
	
	if(NULL == node)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	node->data = data;
	node->children[LEFT] = NULL; 
	node->children[RIGHT] = NULL;
	node->height = 1;
	
	return node;
}




int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *node = NULL;

	assert(NULL != tree);
	assert(NULL != data);
	
	node = CreateNode(data);
	
	tree->root.children[LEFT] = AVLInsert_Ax(tree, data, tree->root.children[LEFT], node);
	tree->root.height = tree->root.children[LEFT]->height + 1; 
	return 1;
}

void AVLDestroy(avl_t *tree)
{
	assert(NULL != tree);
	Destroy_Ax(tree->root.children[LEFT]);
	free(tree);
}

size_t AVLHeight(const avl_t *tree)
{
	assert(NULL != tree);
	return tree->root.height;
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(NULL != tree);
	return tree->root.children[LEFT] == NULL;
}

void *AVLFind(const avl_t *tree, const void *key_data)
{
	assert(NULL != tree);
	assert(NULL != key_data);
	return Find_Ax(tree, tree->root.children[LEFT], key_data);
}

/*******************************************************************************/

void *Find_Ax(const avl_t *tree, avl_node_t *node, const void *key_data)
{	
	child_t child = 0;	
	
	if(NULL == node)
	{
		return NULL;
	}
	
	if(tree->cmp_func(key_data, GetData(node)) < 0)
	{
		child = RIGHT;	
	}
	
	else if(tree->cmp_func(key_data, GetData(node)) > 0)
	{
		child = LEFT;	
	}
	else
	{
		return GetData(node);
	}
	
	return Find_Ax(tree, node->children[child], key_data);
}



avl_t *AVLCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	avl_t *avl = NULL;

	assert(NULL != cmp_func);

	avl = malloc(sizeof(avl_t));
	if(NULL == avl)
	{
		LOGERROR("SORRY, NO MEMORY FOR YOU");
		return NULL;
	}
	avl->cmp_func = cmp_func;
	avl->root.children[LEFT] = NULL;
	avl->root.children[RIGHT] = NULL;
	avl->root.data = avl;
	avl->root.height = 1;

	return avl;
}

void Destroy_Ax(avl_node_t *node)
{	
	if(node)
	{
		Destroy_Ax(node->children[LEFT]);
		Destroy_Ax(node->children[RIGHT]);
	}
	free(node);
}


void *AVLInsert_Ax(avl_t *tree, void *data, avl_node_t *node, avl_node_t *new)
{
	child_t child = 0;
	
	if(NULL == node)
	{
		return new;
	}
	
	if(tree->cmp_func(data, GetData(node)) < 0)
	{
		child = RIGHT;	
	}
	
	else if(tree->cmp_func(data, GetData(node)) > 0)
	{
		child = LEFT;	
	}
	else
	{
		return GetData(node);
	}
	
	node->children[child] = AVLInsert_Ax(tree, data, node->children[child], new);
	

	if (GetHeight(node) <= GetHeight(node->children[child]))
	{
		node->height = node->children[child]->height + 1;
	}
	return node;

}

void *GetData(avl_node_t *node)
{
	if (node == NULL)
	{
		return NULL;
	}    
	return node->data;
}


size_t GetHeight(avl_node_t *node)
{
	if (node == NULL)
	{
		return 0;
	}    
	return node->height;
}

void PrintTree(avl_t *tree)
{
	avl_node_t *root = tree->root.children[LEFT];
	
	Print2D(root, 0);
}

static void Print2D(avl_node_t *root, int space)
{
	int i = 0;
	if (root == NULL)
	{
		return;
	}
	space += COUNT;
	Print2D(root->children[RIGHT], space);
	
	for(i = COUNT; i < space; ++i)
	{
		printf(" ");
	}
	printf("%d (%lu)\n", *(int*)(root->data), root->height );
	Print2D(root->children[LEFT], space);
}



/*
void SetHeight(avl_node_t *node, size_t height)
{
	if (node == NULL)
	{
		return;
	}    
	node->height = height;
}

int GetBalance(avl_node_t *node)
{
	if (node == NULL)
	{
		return 0;
	}
	return GetHeight(node->left) - GetHeight(node->right);
}
*/












