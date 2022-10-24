#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t;
/*
typedef struct bst_node *bst_node_t;
*/


/*
struct bst
{
    struct bst_node root;
	int (*cmp_func)(const void *data, const void *key_data);
}

typedef enum child_node_pos
{
	LEFT = 0;
	RIGHT = 1;
	NUM_CHILD_NODES = 2;
} child_node_pos_t;

struct bst_node
{
    bst_node_t *parent;
	bst_node_t *childrens[NUM_CHILD_NODES];
    void *data;
}
*/

/* CONSTRUCT & DESTRUCT FUNCS */

/*
 * Description: The function creates an instance of the binary search tree.
 * Parameters: @cmp_func is function to compare data
 * Return: pointer to the new instance of binary search tree.
 * Complexity: O(1)
 */
bst_t *BSTCreate(int (*cmp_func)(const void *data, const void *key_data));

/*
 * Description: The function destroys an instance of the binary search tree.
 * Parameters: @tree is an instance which should be destroyed.
 * Return: Nothing
 * Complexity: O(n)
*/
void BSTDestroy(bst_t *tree);

/* ADD & REMOVE FUNCS */

/*
* Description: The function inserts a new element into the binary search tree.
* Parameters: 
*  @tree is an instance of binary search tree.
*  @data is a pointer points to a value which should be inserted in the binary search tree.
* Return: @bst_iter_t that represents a new element
* or NULL on failure
* Complexity: 
*    WC: O(n)
*    AVR: O(log(n))
*    Space: O(1)
*/
bst_iter_t BSTInsert(bst_t *tree, void *data);

/*
* Description: The function removes an element represented by @iter.
* Parameters: 
*  @iter is an iterator that represents an element to be removed.
* Return: @bst_iter_t that represents the parent of the removed element.
* Complexity: 
*    WC: O(log(n))
*    AVR: O(log(n))
*    Space: O(1)
*/
bst_iter_t BSTRemove(bst_iter_t iter);

/* UTILITY FUNCS */

/*
* Description: The function returns the count of elements in the tree.
* Parameters: 
*  @tree is a binary tree.
* Return: count of elements
* Complexity: 
*    BC: O(n)
*    WC: O(n)
*    AVR: O(n)
*    Space: O(1)
*/
size_t BSTSize(const bst_t *tree);

/*
* Description: The function allows to know that the BST is empty.
* Parameters: 
*  @tree pointer to the instance of binary search tree.
* Return: bool
* Complexity: O(1)
*/
int BSTIsEmpty(const bst_t *tree);

/* ITERATOR FUNCS */

/*
* Description: The function returns an iterator to the root of the tree.
* Parameters: 
*  @tree is a binary search tree.
* Return: @bst_iter_t represents the root of the tree
* Complexity: 
*	WC: O(1)
*	AVR: O(log(n))
*	Space: O(1)
*/
bst_iter_t BSTBegin(const bst_t *tree);

/*
* Description: The function returns an iterator to the last element of the tree (one after 
* the element with the largest of the user's data).
* Parameters: 
*  @tree is a binary search tree.
* Return: @bst_iter_t represents the last (not valid) element of the tree
* Complexity: O(1)
*/
bst_iter_t BSTEnd(const bst_t *tree);

/*
* Description: The function returns an iterator to the next in order element of the given iterator.
* Parameters: 
*  @iter is an iterator.
* Return: @bst_iter_t represents the right child of the  next in order element given iterator
* Complexity: 
*    BC: O(log(n))
*    WC: O(log(n))
*    AVR: O(log(n))
*    Space: O(1)
*/
bst_iter_t BSTNext(const bst_iter_t iter);

/*
* Description: The function returns an iterator to the previous in order element of the given iterator.
* Parameters: 
*  @iter is an iterator.
* Return: @bst_iter_t represents the previous in order element of the given iterator
* Complexity: 
*    BC: O(log(n))
*    WC: O(log(n))
*    AVR: O(log(n))
*    Space: O(1)
*/
bst_iter_t BSTPrev(const bst_iter_t iter);

/*
* Description: The function compares two iterators.
* Parameters: 
*  @iter1, @iter2 are iterators.
* Return: bool, 0 - FALSE, 1 - TRUE
* Complexity: O(1)
*/
int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2);

/* GETTERS */

/*
 * Description: The function gets the data at the element represented by @iter.
 * Parameters: @iter represents some element in the binary tree.
 * Return: @void* is a pointer to the data contained at the element represented by @iter.
 * Complexity: O(1)
 */
void *BSTGetData(const bst_iter_t iter);


/* ACTION FUNCS */

/*
 * Description: The function finds the first element in a given span using @cmp_func function
 * to compare data from each element with @key_data.
 * Parameters: 
 *  @tree is an instance of tree.
 *  @key_data is data to be found.
 * Return: 
 *  @bst_iter_t reprensents the element which was found or same as BSTEnd() if @key_data was not found.
 * Complexity: 
 *    WC: O(n)
 *    AVR: O(log(n))
 *    Space: O(1)
 */
bst_iter_t BSTFind(const bst_t *tree, void *key_data);

/*
 * Description: The function applies any given function to each element in the range.
 * Parameters: 
 *  @from is an iterator representing the begining of the range (included).
 *  @to is an iterator representing the end of the range (not included).
 *  @func is a function which performs some action to each node in the binary tree.
 *  @param is a value required for function action.
 * Return: @int - the return type of action func
 *  @0, if the function executes successfully.
 *  @NonZero, if the function executes not successfully.
 * Complexity: 
 *    WC: O(n)
 *    AVR: O(n)
 *    Space: O(1)
 */
int BSTForEach(bst_iter_t from, const bst_iter_t to,
		int (*action_func)(void *data, void *params), void *param);

#endif /* __BST_H__ */
