/*****************************************************
* Topic: Algorithms                                  *                 
* Author: Rudnik Ilia                                *
* Date: 22.10.2022                                   *
* Reviewer: Oury & Vadim                             *
* Review status: reviewed                            *
*****************************************************/

#include <stddef.h> /*size_t*/
#include <stdio.h>
#include <assert.h> 
#include <stdlib.h> /*malloc*/
#include <limits.h>
#include <string.h> /*memcpy*/
#include <alloca.h> 


#include "sorts.h"


static void Swap(int *x, int *y)
{
    int tmp = 0;
    
    assert(NULL != x);
    assert(NULL != y);
    
    tmp = *x;
    *x = *y;
    *y = tmp;
}

void InsertionSort(int *arr, size_t size)
{	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	
	for(i = 1; i < size; ++i){
		for(j = i; j > 0 && arr[j-1] > arr[j]; --j)
		{
			 Swap(&arr[j], &arr[j-1]);
		}
	}
}

void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	
    	for (i = 0; i < size - 1; i++)
    	{
		for (j = 0; j < size - i - 1; ++j)
		{
		    if (arr[j] > arr[j + 1])
		    {
		        Swap(&arr[j], &arr[j + 1]);
	            }
		}        
	}
}

void SelectionSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	size_t min = 0;
	
	assert(NULL != arr);
	
	for(i = 0; i < size - 1; ++i)
	{
		min = i;
		for(j = i + 1; j < size; ++j)
		{
			if(arr[min] > arr[j])
			{
				min = j;
			}
		}
		Swap(&arr[i], &arr[min]);
	}
}

void CountingSort(int *arr, size_t size)
{
	size_t i = 0; 
	size_t size_of_tmp = 0;
	int min = 0;
	int max = 0; 
	int *tmp_arr = NULL; 
	int *res_arr = NULL;
	
	assert(NULL != arr);
 
	min = max = arr[0];
	
	for(i = 1; i < size ; ++i) 
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	size_of_tmp  = max - min + 1;

	tmp_arr = (int*)calloc(size_of_tmp, sizeof(int));
	
	if(tmp_arr == NULL)
	{
		perror("NO MEMORY!");
		return;
	}
	
	res_arr = (int*)malloc(size * sizeof(int));
	
	if(res_arr == NULL)
	{
		free(tmp_arr);
		perror("NO MEMORY!");
		return;
	}

	for(i = 0; i < size; ++i)
	{
		++tmp_arr[arr[i] - min];
	}
	
	
	for(i = 1; i < size_of_tmp; ++i)
	{
		tmp_arr[i] = tmp_arr[i] + tmp_arr[i-1];
	}
	

	for(i = 0; i < size; ++i)
	{
		res_arr[tmp_arr[arr[i] - min] - 1] = arr[i];
		--tmp_arr[arr[i] - min];
	}


	for(i = 0; i < size; ++i)
	{ 
		arr[i] = res_arr[i];
	}


	free(tmp_arr);
	free(res_arr);
	
	tmp_arr = NULL; 
	res_arr = NULL;
}

static void Count(int *arr, int size, int place) {

	int i = 0;
	int freq[10] = {0};
	int *output = NULL;
	
	assert(NULL != arr);
	
	output = (int*)malloc(size * sizeof(int));
	
	if(output == NULL)
	{
		perror("NO MEMORY!");
		return;
	}
	
	for (i = 0; i < size; i++)
	{
		freq[(arr[i] / place) % 10]++;
	}

	for (i = 1; i < 10; i++)
	{
		freq[i] += freq[i - 1];
	}
	
	for (i = size - 1; i >= 0; i--) 
	{
		output[freq[(arr[i] / place) % 10] - 1] = arr[i];

		freq[(arr[i] / place) % 10]--;
	}

	for (i = 0; i < size; i++)
	{
		arr[i] = output[i];
	}

	free(output);
	output = NULL;
}

void RadixSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t place = 0;
	int max = 0;
	
	assert(NULL != arr);
	
	max = arr[0];
	for(i = 1; i < size; ++i)
	{
		if(max < arr[i])
		{
			max = arr[i];
		}
	}
	
	for(place = 1; max/place > 0; place *= 10)
	{
		Count(arr, size, place);
	}
}


int MergeSort(int *arr_to_sort, size_t num_elements)
{
	size_t i = 0;
	size_t li = 0;
	size_t ri = 0;

	int *left = NULL;
	int *right = NULL;
	
	size_t sizeleft = num_elements / 2;
	size_t sizeright = num_elements - sizeleft;
	
	left = (int*)alloca(sizeleft * sizeof(int));
	right= (int*)alloca(sizeright * sizeof(int));

	memset(left,0, sizeleft * sizeof(int));
	memset(right,0, sizeright * sizeof(int));	
	
	if(num_elements == 1)
	{
		return 0;
	}

	for(i = 0; i < num_elements; ++i)
	{
		if(i < sizeleft)
		{
			left[li] = arr_to_sort[i];
			li++;
		}
		else
		{
			right[ri] = arr_to_sort[i];
			ri++;
		}
	}

	MergeSort(left, sizeleft);
	MergeSort(right, sizeright);
	
	li = 0;
	ri = 0;
	for(i = 0; i < num_elements; ++i)
	{
		if((left[li] <= right[ri] && li < sizeleft) || ri == sizeright)
		{
			arr_to_sort[i] = left[li];
			li++;
		}
		else
		{
			arr_to_sort[i] = right[ri];
			ri++;
		}
	}
	return 0;
}

static void SwapVoid(void *a, void *b, size_t size)
{	
	void *tmp = NULL;
	tmp = alloca(sizeof(void*));
	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);
}

void _quicksort(void *arr, size_t elems, size_t size_elem, int low, int high, int (*is_before)(const void *elem1, const void *elem2))
{
	void *pivot = NULL;
	int i = 0;
	int j = 0;
	
	if(low < high)
	{
		pivot = (char*)arr + (elems)*size_elem;
		i = low;
		j = high;
		
		while(i < j) 
		{
			while((is_before((char*)arr + i, pivot) == 1) && i <= high)
			{
				i+=size_elem;
			}
			while((is_before((char*)arr + j, pivot) == 2) && j >= low)
			{
				j-=size_elem;
			}
			if(i < j) 
			{
				SwapVoid((char*)arr + i, (char*)arr + j, size_elem);
			}
		}

		SwapVoid((char*)arr + j, pivot, size_elem);
	
		_quicksort(arr, elems-1, size_elem, low, j-size_elem, is_before);
		_quicksort(arr, elems-1, size_elem, j+size_elem, high, is_before);
	}
}
int QuickSort(void *arr_to_sort, size_t num_elements, size_t elem_size,  int (*is_before)(const void *elem1, const void *elem2))
{
	_quicksort(arr_to_sort, num_elements-1, elem_size, 0, num_elements*elem_size - elem_size, is_before);
	return 0;
}









