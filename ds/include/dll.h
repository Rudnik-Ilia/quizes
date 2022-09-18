#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h> /* size_t */


typedef struct dllist dllist_t;
typedef struct dll_node *dllist_iter_t;


dllist_t *SpecialDLLCreate(void);
/* CONSTRUCT & DESTRUCT FUNCS */

/*
 * Description: The function creates an instance of doubly linked list.
 * Parameters: Nothing
 * Return: pointer to the new instance of doubly linked list
 * Complexity: O(1)
 */
dllist_t *DLLCreate(void);

/*
 * Description: The function destroys an instance of doubly linked list.
 * Parameters: @list is an instance which should be destroyed.
 * Return: Nothing
 * Complexity: O(n)
 */
void DLLDestroy(dllist_t *list);


/* ADD & REMOVE FUNCS */

/*
* Description: The function pushes a new element to the front of the list.
* Parameters: 
*  @list is a linked list, where element should be pushed.
*  @data is a pointer points to a value which should be pushed in the linked list.
* Return: @dllist_iter_t that represents a new element
* or NULL on failure
* Complexity: O(1)
*/
dllist_iter_t DLLPushFront(dllist_t *list, void *data);

/*
* Description: The function pushes a new element to the back of the list.
* Parameters: 
*  @list is a linked list, where element should be pushed.
*  @data is a pointer points to a value which should be pushed in the linked list.
* Return: @dllist_iter_t that represents to a new element
* or NULL on failure
* Complexity: O(1)
*/
dllist_iter_t DLLPushBack(dllist_t *list, void *data);

/*
* Description: The function inserts a new element before an element represented by iterator.
* Parameters: 
*  @iter is an iterator representing an element in the linked list.
*  @data is a pointer points to a value which should be inserted in the linked list.
* Return: @dllist_iter_t that represents a new element
* or NULL on failure
* Complexity: O(1)
*/
dllist_iter_t DLLInsert(dllist_iter_t iter, void *data);

/*
* Description: The function removes an element represented by iterator.
* Parameters: 
*  @iter is an iterator represents to an element.
* Return: @dllist_iter_t that represents the next element
* Complexity: O(1)
*/
dllist_iter_t DLLRemove(dllist_iter_t iter);

/*
* Description: The function returns data from the front of the list.
* Parameters: 
*  @list is a linked list, where element should be popped.
* Return: data from new front element (same as dllistBegin)
* Complexity: O(1)
*/
void *DLLPopFront(dllist_t *list);

/*
* Description: The function returns data from the back of the list.
* Parameters: 
*  @list is a linked list, where element should be popped.
* Return: data from the back element of list (same as dllistEnd)
* Complexity: O(1)
*/
void *DLLPopBack(dllist_t *list);


/* UTILITY FUNCS */

/*
* Description: The function returns the count of elements in the list.
* Parameters: 
*  @list is a linked list.
* Return: count of elements
* Complexity: O(n)
*/
size_t DLLSize(const dllist_t *list);

/*
* Description: The function allows to know that list is empty.
* Parameters: 
*  @list is a linked list.
* Return: bool
* Complexity: O(1)
*/
int DLLIsEmpty(const dllist_t *list);


/* ITERATOR FUNCS */

/*
* Description: The function returns an iterator to the front element of the list.
* Parameters: 
*  @list is a linked list.
* Return: @dllist_iter_t represents front element of the list
* Complexity: O(1)
*/
dllist_iter_t DLLBegin(const dllist_t *list);

/*
* Description: The function returns an iterator to the last element of the list (one after element with user's data).
* Parameters: 
*  @list is a linked list.
* Return: @dllist_iter_t represents the last element of the list
* Complexity: O(1)
*/
dllist_iter_t DLLEnd(const dllist_t *list);

/*
* Description: The function returns an iterator to the next element relatively to the given iterator.
* Parameters: 
*  @iter is an iterator.
* Return: @dllist_iter_t represents the next element relatively to given iterator
* Complexity: O(1)
*/
dllist_iter_t DLLNext(const dllist_iter_t iter);

/*
* Description: The function returns an iterator to the previous element relatively to the given iterator.
* Parameters: 
*  @iter is an iterator.
* Return: @dllist_iter_t represents the previous element relatively to given iterator
* Complexity: O(1)
*/
dllist_iter_t DLLPrev(const dllist_iter_t iter);

/*
* Description: The function compares two iterators.
* Parameters: 
*  @iter1, @iter2 are iterators.
* Return: bool
* Complexity: O(1)
*/
int DLLIsEqualIter(const dllist_iter_t iter1, const dllist_iter_t iter2);


/* GETTERS AND SETTERS */

/*
 * Description: The function sets a data at the element pointed to by @iter.
 * Parameters: @iter represents some element in the linked list.
 *  @data is a pointer to the data, which should be stored in the list
 * Return: Nothing
 * Complexity: O(1)
 */
void DLLSetData(dllist_iter_t iter, void *data);

/*
 * Description: The function gets a data at the represented by @iter.
 * Parameters: @iter represents some element in the linked list.
 * Return: @void* is a pointer to a data contained at the element represented by @iter.
 * Complexity: O(1)
 */
void *DLLGetData(const dllist_iter_t iter);


/* ACTION FUNCS */

/*
 * Description: The function finds the first element in a given span using @is_match function
 * to compare data from each element with @param.
 * Parameters: 
 *  @from is an iterator representing the begining of the range (included).
 *  @to is an iterator representing the end of the range (not included).
 *  @is_match is a user's function to compare data from element and @param
 *  @param is an parametr to compare with data in each element
 * Return: 
 *  @dllist_iter_t reprensents an element which was found.
 *  @NULL is a NULL pointer, if node was not found.
 * Complexity: O(n)
 */
dllist_iter_t DLLFind(const dllist_iter_t from, const dllist_iter_t to,
		int (*is_match_func)(const void *data, void *params), void *param);

/*
 * Description: The function applies any given function to each element in the range.
 * Parameters: 
 *  @from is an iterator representing the begining of the range (included).
 *  @to is an iterator representing the end of the range (not included).
 *  @func is a function which performs some action to each node in the linked list.
 *  @param is a value required for function action.
 * Return: @int - the return type of action func
 *  @0, if the function executes successfully.
 *  @NonZero, if the function executes not successfully.
 * Complexity: O(n)
 */
 
int DLLForEach(const dllist_iter_t from, const dllist_iter_t to,
		int (*action_func)(void *data, void *params), void *param);

/*
 * Description: The function cuts a segment from a list and inserts it before the iterator dest, which is an element of another list. 
 * The segment to be cut starts at iterator_from up to iterator_to. 
 * Parameters: 
 *  @from is an iterator representing the begining of the segment (included).
 *  @to is an iterator representing the end of the segment (not included).
 *  @dest is an iterator to be connected with the segment at the end of the segment
 * Return: nothing 
 * Complexity: O(1)
 */

void DLLSplice(dllist_iter_t from, dllist_iter_t to, dllist_iter_t dest);

/*
 * Description: The function finds all occurences of the @param in a given span using
 * @is_match function to compare data from each element with @param.
 * Parameters: 
 *  @from is an iterator representing the begining of the range (included).
 *  @to is an iterator representing the end of the range (not included).
 *  @is_match is a user's function to compare data from element and @param
 *  @param is an parametr to compare with data in each element
 *  @output_list is a list, where all occurences will be inserted (at the back)
 * Return: 
 *  @int number of elements found
 *  -1 if Error
 * Complexity: O(n)
 */
int DLLMultiFind(const dllist_iter_t from, const dllist_iter_t to,
		int (*is_match_func)(const void *data, void *params), void *param, dllist_t *output_list);


#endif /* __DLL_H__ */
