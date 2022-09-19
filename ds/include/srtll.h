#ifndef __SORTED_LL_H_
#define __SORTED_LL_H_

#include <stddef.h> /* size_t */

typedef struct sorted_list sorted_list_t;

typedef struct sorted_list_iterator sorted_list_iterator_t;

/*
struct sorted_list_iterator
{
	#ifndef NDEBUG
	sorted_list *list;
	#endif
	
	dllist_iter_t dll_iter;
};

*/

/* CONSTRUCT & DESTRUCT FUNCS */

/*
 * Description: The function creates an instance of a sorted linked list.
 * Parameters: @cmp_func - basic function that defines the order of nodes in the list
 * Return: pointer to the new instance of the sorted linked list
 * Complexity: O(1)
 */
sorted_list_t *SortedLLCreate(int (*cmp_func)(const void *data1, const void *data2)); 

/*
 * Description: The function destroys an instance of a sorted linked list.
 * Parameters: @list is the instance which should be destroyed.
 * Return: Nothing
 * Complexity: O(n)
 */
void SortedLLDestroy(sorted_list_t *list);

/* ADD & REMOVE FUNCS */

/*
* Description: The function inserts a new element before the element represented by the iterator.
* Parameters: 
*  @list is a sorted linked list where data will be inserted.
*  @data is a pointer that points to a value which should be inserted in the linked list.
* Return: @sorted_list_iterator_t that represents a new element
* or the iterator representing the end of the list on failure
* Complexity: O(n)
*/
sorted_list_iterator_t SortedLLInsert(sorted_list_t *list, void *data);

/*
* Description: The function removes an element represented by the iterator.
* Parameters: 
*  @iter is an iterator to an element.
* Return: @sorted_list_iterator_t that represents the next element
* Complexity: O(1)
*/
sorted_list_iterator_t SortedLLRemove(sorted_list_iterator_t iter);

/*
 Description: The function removes the front element of the list.
 Parameters: 
 @list is a linked list, where the front element should be popped.
 Return: data of the element that was removed 
 Complexity: O(1)
*/ 
void *SortedLLPopFront(sorted_list_t *list);

/*
* Pescription: The function removes the element from the back of the list.
* Parameters: 
* @list is a linked list, where the last element should be popped.
* Return: data of the element that was removed 
* Complexity: O(1)
*/
void *SortedLLPopBack(sorted_list_t *list);

/* ITERATOR FUNCS */

/*
* Description: The function returns an iterator to the front element of the list.
* Parameters: 
*  @list is a linked list.
* Return: @sorted_list_iterator_t represents the front element of the list
* Complexity: O(1)
*/
sorted_list_iterator_t SortedLLBegin(const sorted_list_t *list);

/*
* Description: The function returns an iterator to the last element of the list (one after the element with the user's data).
* Parameters: 
*  @list is a linked list.
* Return: @sorted_list_iterator_t represents the last element of the list
* Complexity: O(1)
*/
sorted_list_iterator_t SortedLLEnd(const sorted_list_t *list);

/*
* Description: The function returns an iterator to the next element relating to the given iterator.
* Parameters: 
*  @iter is an iterator.
* Return: @sorted_list_iterator_t represents the next element relating to the given iterator
* Complexity: O(1)
*/
sorted_list_iterator_t SortedLLNext(sorted_list_iterator_t iter);

/*
* Description: The function returns an iterator to the previous element relating to the given iterator.
* Parameters: 
*  @iter is an iterator.
* Return: @sorted_list_iterator_t represents the previous element relating to the given iterator
* Complexity: O(1)
*/
sorted_list_iterator_t SortedLLPrev(sorted_list_iterator_t iter);

/*
* Description: The function compares two iterators.
* Parameters: 
*  @iter1, @iter2 are iterators.
* Return: bool
* Complexity: O(1)
*/
int SortedLLIsEqualIter(const sorted_list_iterator_t iter1, const sorted_list_iterator_t iter2);

/* UTILS FUNCS */
/*
* Description: The function checks if the list is empty.
* Parameters: 
*  @list is a sorted linked list.
* Return: bool
* Complexity: O(1)
*/
int SortedLLIsEmpty(const sorted_list_t *list);

/*
* Description: The function returns the count of elements in the list.
* Parameters: 
*  @list is a sorted linked list.
* Return: number of elements
* Complexity: O(n)
*/
size_t SortedLLSize(const sorted_list_t *list);

/* GETTERS AND SETTERS */

/*
 * Description: The function gets the data from the element represented by @iter.
 * Parameters: @iter represents some element in the linked list.
 * Return: @void* is a pointer to a data contained at the element represented by @iter.
 * Complexity: O(1)
 */
void *SortedLLGetData(const sorted_list_iterator_t iter);

/* ACTION FUNCTIONS */

/*
 * Description: The function applies any given function to each element in the range.
 * Parameters: 
 *  @from is an iterator representing the begining of the range (included).
 *  @to is an iterator representing the end of the range (not included).
 *  @action_func is a function which performs some action to each node in the linked list.
 *  @params is a value required for function action.
 * Return: @int - the return type of action func
 *  @0, if the function executes successfully.
 *  @NonZero, if the function executes not successfully.
 * Complexity: O(n)
 */
int SortedLLForEach(const sorted_list_iterator_t from, const sorted_list_iterator_t to, int (*action_func)(void *data, void *params), void *params);

/*
 * Description: The function finds the first element in a given span where @data matches element data 
 *	using default compare function
 * Parameters: 
 *  @list is a sorted linked list.
 *  @from is an iterator representing the begining of the range (included).
 *  @to is an iterator representing the end of the range (not included).
 *  @data is a data to compare with data in each element using default compare function
 * Return: 
 *  @sorted_list_iterator_t reprensents the element which was found.
 *  @to, if the element was not found.
 * Complexity: O(n)
 */

sorted_list_iterator_t SortedLLFind(const sorted_list_t *list, const sorted_list_iterator_t from, const sorted_list_iterator_t to, const void *data);

/*
 * Description: The function finds the first element in a given span using @is_match function
 * to compare data from each element with @params.
 * Parameters: 
 *  @from is an iterator representing the begining of the range (included).
 *  @to is an iterator representing the end of the range (not included).
 *  @is_match is a user's function to compare data from element and @param
 *  @params is a parameter to compare with data in each element
 * Return: 
 *  @sorted_list_iterator_t reprensents the element which was found.
 *  @to, if the element was not found.
 * Complexity: O(n)
 */
sorted_list_iterator_t SortedLLFindIf(const sorted_list_iterator_t from, const sorted_list_iterator_t to, int (*is_match)(void *data, void *params), void *params);

/*
 * Description: Merges a source list to a destination list. Source list will be emptied
 * Parameters: 
 *  @src - pointer to the source list
 *  @dest - pointer to the dest list, where elements will be moved
 * Return: 
 *  @sorted_list_t pointer to the dest list 
 *  Attention: after merge @src is a valid empty sorted list 
 * Complexity: O(n)
 */
sorted_list_t *SortedLLMerge(sorted_list_t *dest, sorted_list_t *src);


#endif /* __SORTED_LL_H_ */
