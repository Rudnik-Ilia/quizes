#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h>

/*
 * Description: The function sorts a given array of integers.
 * Parameters:
 * 	@arr is an array of integers
 *	@size is a size of the array
 * Return: Nothing
 * Time complexity: 
 * 	@Best:    O(n)
 * 	@Average: O(n^2)
 * 	@Worst:   O(n^2)
 * Space comlexity: O(1)
 */
void BubbleSort(int *arr, size_t size);

/*
 * Description: The function sorts a given array of integers.
 * Parameters:
 * 	@arr is an array of integers
 *	@size is a size of the array
 * Return: Nothing
 * Time complexity: 
 *	@Best:    O(n^2) 
 * 	@Average: O(n^2)
 * 	@Worst:   O(n^2)
 * Space complexity: O(1)
 */
void SelectionSort(int *arr, size_t size); 

/*
 * Description: The function sorts a given array of integers.
 * Parameters:
 * 	@arr is an array of integers
 *	@size is a size of the array
 * Return: Nothing
 * Time complexity: 
 *	@Best:    O(n)
 *	@Average: O(n^2)
 * 	@Worst:   O(n^2)
 * Space complexity: O(1)
 */
void InsertionSort(int *arr, size_t size); 

/*
 * Description: The function sorts a given array of integers.
 * Parameters:
 * 	@arr is an array of integers
 *	@size is a size of the array
 * Return: Nothing
 * Time complexity:
 * 	@Best:    O(n + k)
 *  @Average: O(n + k)
 * 	@Worst:   O(n + k)
 *  	@k = (maximum element - minimum element + 1)
 * Space complexity: O(n)
 */
void CountingSort(int *arr, size_t size);

/*
 * Description: The function sorts a given array of integers.
 * Parameters:
 * 	@arr is an array of integers
 *	@size is a size of the array
 * Return: Nothing
 * Complexity:
 * 	@Best:    O(d * n)
 *  @Average: O(d * (n + k))
 * 	@Worst:   O(n^2)
 *      @d is the number of digits in the maximum value
 *      @k is the number of buckets
 * Space complexity: O()
 */
void RadixSort(int *arr, size_t size);

/*
 * Description: The function sorts a given array.
 * Parameters:
 * 	@arr_to_sort is an array 
 *	@num_elements is a size of the array
 *	@elem_size is a size of one element in array
 *	@is_before function, that returns 1 if @elem1 should be placed before @elem2
 * Return: 0 on success, non-zero on fail
 * Time complexity: 
 *	@Best:    O(n*log(n))
 *	@Average: O(n*log(n))
 * 	@Worst:   O(n*log(n))
 * Space complexity: O(1)
 */
 
int QuickSort(void *arr_to_sort, size_t num_elements, size_t elem_size,  int (*is_before)(const void *elem1, const void *elem2));

/*
 * Description: The function sorts a given array.
 * Parameters:
 * 	@arr_to_sort is an array 
 *	@num_elements is a size of the array
 *	@elem_size is a size of one element in array
 *	@is_before function, that returns 1 if @elem1 should be placed before @elem2
 * Return: 0 on success, non-zero on fail
 * Time complexity: 
 *	@Best:    O(n*log(n))
 *	@Average: O(n*log(n))
 * 	@Worst:   O(n*log(n))
 * Space complexity: O(n)
 */
int MergeSort(int *arr_to_sort, size_t num_elements);



#endif
