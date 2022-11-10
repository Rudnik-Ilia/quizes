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


avl_node_t *CreateNode(void *data);
void *AVLInsert_Ax(avl_t *tree, void *data, avl_node_t *node, avl_node_t *new);
void *GetData(avl_node_t *node);
void Destroy_Ax(avl_node_t *node);
size_t GetHeight(avl_node_t *node);
avl_node_t *CreateNode(void *data);
void *Find_Ax(const avl_t *tree, avl_node_t *node, const void *key_data);

int InOrder(avl_node_t *node, int (*action_func)(void *data, void *params), void *param);
int PreOrder(avl_node_t *node, int (*action_func)(void *data, void *params), void *param);
int PostOrder(avl_node_t *node, int (*action_func)(void *data, void *params), void *param);

static void Print2D(avl_node_t *root, int space);

int GetBalance(avl_node_t *node);
avl_node_t * MinValueNode(avl_node_t * node);

avl_node_t *LeftRotate(avl_node_t *x);
avl_node_t *RightRotate(avl_node_t *y); 

avl_node_t *Delete(avl_t *tree, avl_node_t *node , const void* data);

static int Count(void *data, void *count);



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
	avl->root.height = 0;

	return avl;
}

void AVLDestroy(avl_t *tree)
{
	assert(NULL != tree);
	
	Destroy_Ax(tree->root.children[LEFT]);
	free(tree);
}

size_t AVLHeight(const avl_t *tree)
{
	avl_node_t *node = NULL;
	
	assert(NULL != tree);
	
	node = tree->root.children[LEFT];
	return NULL == node ? 0: node->height;
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

int AVLForEach(avl_t *tree, int (*action_func)(void *data, void *params), void *param, bst_traversal_type_t order)
{	
	int st = 0;
	switch (order){
	
		case IN_ORDER :
		
			st = InOrder(tree->root.children[LEFT], action_func, param);
			break;
		case PRE_ORDER:
			st = PreOrder(tree->root.children[LEFT], action_func, param);
			break;	
		case POST_ORDER:
			st = PostOrder(tree->root.children[LEFT], action_func, param);
			break;	
	}
		
	return st;
}

size_t AVLSize(const avl_t *tree)
{
    size_t count = 0;
    AVLForEach((avl_t*)tree, Count, &count, PRE_ORDER);
    return count;
}
			
void AVLRemove(avl_t *tree, const void *data)
{
	Delete(tree, tree->root.children[LEFT], data);
}


avl_node_t *Delete(avl_t *tree, avl_node_t *node , const void* data)
{
 	avl_node_t  *temp = NULL;
 	
 	int balance = 0;
 	
	if (node == NULL)
	{
		return node;
	}
	if(tree->cmp_func(data, GetData(node)) < 0)
	{
		
        	node->children[LEFT] = Delete(tree, node->children[LEFT], data);

	}
	else if(tree->cmp_func(data, GetData(node)) > 0)
	{
		node->children[RIGHT] = Delete(tree, node->children[RIGHT], data);
	}
	else
	{
		if( node->children[LEFT] == NULL || node->children[RIGHT] == NULL)
		{
			temp = node->children[LEFT] ? node->children[LEFT] : node->children[RIGHT];


			if (temp == NULL)
			{
				temp = node;
				node = NULL;
				free(temp);
			}
			else 
			{
				*node = *temp; 
				free(temp);
			}

		}
		else
		{

			temp = MinValueNode(node->children[RIGHT]);
			node->data= temp->data;
			node->children[RIGHT] = Delete(tree, node->children[RIGHT], temp->data);
		}
	}
	if (node== NULL)
	{
		return node;
	}
	
	node->height = 1 + MAX(GetHeight(node->children[LEFT]), GetHeight(node->children[RIGHT]));
	
	balance = GetBalance(node);
	
	printf("BALANCE: %d\n", GetBalance(node));
	
	if (balance > 1 && GetBalance(node->children[LEFT]) >= 0)
	{
        	return RightRotate(node);
 	}
	if (balance > 1 && GetBalance(node->children[LEFT]) < 0)
	{
		node->children[LEFT] =  LeftRotate(node->children[LEFT]);
		return RightRotate(node);
	}
	if (balance < -1 && GetBalance(node->children[RIGHT]) <= 0)
	{
		return LeftRotate(node);
	}
	if (balance < -1 && GetBalance(node->children[RIGHT]) > 0)
	{
		node->children[RIGHT] = RightRotate(node->children[RIGHT]);
		return LeftRotate(node);
	}
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

	return 0;
}
/************************************************************************************************************************/

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

void *Find_Ax(const avl_t *tree, avl_node_t *node, const void *key_data)
{	
	child_t child = 0;	
	
	if(NULL == node)
	{
		return NULL;
	}
	
	if(tree->cmp_func(key_data, GetData(node)) < 0)
	{
		child = LEFT;	
	}
	
	else if(tree->cmp_func(key_data, GetData(node)) > 0)
	{
		child = RIGHT;	
	}
	else
	{
		return GetData(node);
	}
	
	return Find_Ax(tree, node->children[child], key_data);
}


void *AVLInsert_Ax(avl_t *tree, void *data, avl_node_t *node, avl_node_t *new)
{
	child_t child = 0;
	int balance = 0;
	
	if(NULL == node)
	{
		return new;
	}
	if(tree->cmp_func(data, GetData(node)) < 0)
	{
		child = LEFT;	
	}
	else if(tree->cmp_func(data, GetData(node)) > 0)
	{
		child = RIGHT;	
	}
	else
	{
		return GetData(node);
	}
	node->children[child] = AVLInsert_Ax(tree, data, node->children[child], new);
	/*
	if (GetHeight(node) <= GetHeight(node->children[child]))
	{
		node->height = node->children[child]->height + 1;
	}
	
	node->children[child] = AVLInsert_Ax(tree, data, node->children[child], new);
	printf("BALANCE: %d\n", GetBalance(node));
*/
	node->height = 1 + MAX(GetHeight(node->children[LEFT]),GetHeight(node->children[RIGHT]));
    
	balance = GetBalance(node);

	if (balance > 1 && *(int*)data < *(int*)(node->children[LEFT]->data))
	{
		return RightRotate(node);
	}
	if (balance < -1 && *(int*)data > *(int*)(node->children[RIGHT]->data))
	{
		return LeftRotate(node);
	}
	if (balance > 1 && *(int*)data > *(int*)(node->children[LEFT]->data))
	{                             ;
		node->children[LEFT] =  LeftRotate(node->children[LEFT]);
		return RightRotate(node);
	}
	if (balance < -1 && *(int*)data < *(int*)(node->children[RIGHT]->data))
	{
		node->children[RIGHT] = RightRotate(node->children[RIGHT]);
		return LeftRotate(node);
	}
	return node;

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

avl_node_t * MinValueNode(avl_node_t * node)
{
	avl_node_t *current = node;
 
	while (current->children[LEFT] != NULL)
	{
		current = current->children[LEFT];
	}
	return current;
}

static int Count(void *data, void *count)
{
    (void)data;
    ++*(size_t*)count;

    return 0;
}

int InOrder(avl_node_t *node, int (*action_func)(void *data, void *params), void *param)
{	
	int st = 0;
	if(node){
		InOrder(node->children[LEFT], action_func, param);
		st = action_func(node->data, param);
		InOrder(node->children[RIGHT], action_func, param);
	}
	return st;
}

int PreOrder(avl_node_t *node, int (*action_func)(void *data, void *params), void *param)
{
	int st = 0;
	if(node)
	{
		st = action_func(node->data, param);
		PreOrder(node->children[LEFT], action_func, param);
		PreOrder(node->children[RIGHT], action_func, param);
	}
	return st;
}

int PostOrder(avl_node_t *node, int (*action_func)(void *data, void *params), void *param)
{	
	int st = 0;
	if(node)
	{
		PostOrder(node->children[LEFT], action_func, param);
		PostOrder(node->children[RIGHT], action_func, param);
		st = action_func(node->data, param);
	}
	return st;
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

int GetBalance(avl_node_t *node)
{
	if (node == NULL)
	{
		return 0;
	} 
	return GetHeight(node->children[LEFT]) - GetHeight(node->children[RIGHT]);
}

avl_node_t *LeftRotate(avl_node_t *x)
{
    avl_node_t *y = x->children[RIGHT];
    avl_node_t *T2 = y->children[LEFT];
 
    y->children[LEFT] = x;
    x->children[RIGHT] = T2;
 
    x->height = MAX(GetHeight(x->children[LEFT]), GetHeight(x->children[RIGHT])) + 1;
    y->height = MAX(GetHeight(y->children[LEFT]), GetHeight(y->children[RIGHT])) + 1;
 
    return y;
}

avl_node_t *RightRotate(avl_node_t *y) 
{ 
    avl_node_t *x = y->children[LEFT]; 
    avl_node_t *T2 = x->children[RIGHT]; 
   
    x->children[RIGHT] = y; 
    y->children[LEFT]= T2; 
    
    y->height = MAX(GetHeight(y->children[LEFT]), GetHeight(y->children[RIGHT])) + 1; 
    x->height = MAX(GetHeight(x->children[LEFT]), GetHeight(x->children[RIGHT])) + 1; 
   
    return x; 
}

/********************************************************************************************************/

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
	space += 15;
	Print2D(root->children[RIGHT], space);
	
	for(i = 15; i < space; ++i)
	{
		printf(" ");
	}
	printf("%d (%lu)\n", *(int*)(root->data), root->height );
	printf("\n");
	Print2D(root->children[LEFT], space);
}












