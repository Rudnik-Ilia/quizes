#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef struct avl avl_t;


/*
typedef struct avl_node avl_node_t;
struct avl
{
    avl_node *root;
    int (*cmp_func)(const void *data, const void *key_data);
};

enum children { LEFT, RIGHT, MAX_CHILDREN };

struct avl_node 
{
    void *data;
    avl_node_t *children[MAX_CHILDREN];
    size_t height;
};
*/

typedef enum bst_traversal_type
{ 
	PRE_ORDER = 0,
	IN_ORDER = 1,
	POST_ORDER = 2
} bst_traversal_type_t;


/* CONSTRUCT & DESTRUCT FUNCS */

/*
 * Description: The function creates an instance of the AVL tree.
 * Parameters: @cmp_func is function to compare data
 * Return: pointer to the new instance of AVL tree.
 * Complexity: O(1)
 */
avl_t *AVLCreate(int (*cmp_func)(const void *lhs, const void *rhs));

/*
 * Description: The function destroys an instance of the AVL tree.
 * Parameters: @tree is an instance which should be destroyed.
 * Return: Nothing
 * Complexity: O(nlog(n))
*/
void AVLDestroy(avl_t *tree);

/* ADD & REMOVE FUNCS */

/*
* Description: The function inserts a new element into the AVL tree.
* Parameters: 
*  @tree is an instance of AVL tree.
*  @data is a pointer points to a value which should be inserted in the AVL tree.
* Return: 1 if insert was successful and 0 if not.
* Complexity: 
*    WC: O(log(n))
*    AVR: O(log(n))
*    Space: O(1)
*/
int AVLInsert(avl_t *tree, void *data);

/*
* Description: The function removes an element represented by @node.
* Parameters: 
*  @tree is an instance of AVL tree.
*  @data is a pointer points to a value which should be removed in the AVL tree.
* Return: nothing
* Complexity: 
*    WC: O(log(n))
*    AVR: O(log(n))
*    Space: O(1)
*/
void AVLRemove(avl_t *tree, const void *data);

/* UTILITY FUNCS */

/*
* Description: The function returns the count of elements in the tree.
* Parameters: 
*  @tree is an AVL tree.
* Return: count of elements
* Complexity: 
*    BC: O(n)
*    WC: O(n)
*    AVR: O(n)
*    Space: O(1)
*/
size_t AVLSize(const avl_t *tree);

/*
* Description: The function allows to know that the AVL tree is empty.
* Parameters: 
*  @tree pointer to the instance of the AVL tree.
* Return: bool (1 - is empty, 0 - is not empty)
* Complexity: O(1)
*/
int AVLIsEmpty(const avl_t *tree);

/*
* Description: The function returns height of the whole AVL tree.
* Parameters: 
*  @tree is a AVL tree.
* Return: @size_t represents the height of the AVL tree.
* Complexity: 
*	WC: O(1)
*	AVR: O(1)
*	Space: O(1)
*/
size_t AVLHeight(const avl_t *tree);


/* ACTION FUNCS */

/*
 * Description: The function finds the first element in a given AVL tree using @cmp_func function
 * to compare data from each element with @key_data.
 * Parameters: 
 *  @tree is an instance of the AVL tree.
 *  @key_data is data to be found.
 * Return: 
 *  pointer to the data of the found element or NULL if @key_data was not found.
 * Complexity: 
 *    WC: O(log(n))
 *    AVR: O(log(n))
 *    Space: O(1)
 */
void *AVLFind(const avl_t *tree, const void *key_data);

/*
 * Description: The function applies any given function to each element in the range.
 * Parameters: 
 *  @tree is an instance of the AVL tree.
 *  @action_func is a function which performs some action to each node in the binary tree.
 *  @param is a value required for @action_func.
 *  @order is order of traversal represented by enum traversal_order (PRE_ORDER, IN_ORDER, POST_ORDER).
 * Return: @int - the return type of @action_func.
 *  @0, if the function executes successfully.
 *  @NonZero, if the function executes not successfully.
 * Complexity: 
 *    WC: O(nlog(n))
 *    AVR: O(nlog(n))
 *    Space: O(1)
 */
int AVLForEach(avl_t *tree, int (*action_func)(void *data, void *params),
              void *param, bst_traversal_type_t order);
           
void PrintTree(avl_t *tree);


#endif /* __AVL_H__ */


