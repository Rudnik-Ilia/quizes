#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */
#include "../../ds/include/stack.h"

typedef struct node
{
	int data;
	struct node *next;
	
} node_t;

int FibRec(int idx);

int FibIter(int idx);

node_t *ListFlip(node_t *head);

void StackSort(stack_t *stack);



/* String funcs */
size_t StrLen(const char *str);
int StrCmp(const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);


/*
 * Description: The function finds first index of a given array of integers,
 * value of which is equal to @value_to_found.
 * Parameters:
 * 	@arr is an array array of integers
 *	@size is a size of the array
 *	@value_to_found is a value to be found
 * Return: index of first occurence @value_to_found in @arr
 * or -1 if value was not found
 * Time complexity: 
 *	@Best:    O(n*log(n))
 *	@Average: O(n*log(n))
 * 	@Worst:   O(n*log(n))
 * Space complexity: O(1)
 */
ssize_t BinarySearchIter(int *arr, size_t size, int value_to_find);

/*
 * Description: The function finds first index of a given array of integers,
 * value of which is equal to @value_to_found.
 * Parameters:
 * 	@arr is an array array of integers
 *	@size is a size of the array
 *	@value_to_found is a value to be found
 * Return: index of first occurence @value_to_found in @arr
 * or -1 if value was not found
 * Time complexity: 
 *	@Best:    O(n*log(n))
 *	@Average: O(n*log(n))
 * 	@Worst:   O(n*log(n))
 * Space complexity: O(1)
 */
ssize_t BinarySearchRec(int *arr, size_t size, int value_to_find);


#endif /* __RECURSION_H__ */
