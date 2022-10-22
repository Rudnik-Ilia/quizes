/************************************************************/
/* Title: sorts.c                                             
** Author: Ira                                              
** Date: 2022-10-20                                         
** Reviewer: Timofey, Ilia                                        
** Review status:                                          
************************************************************/

#include <stddef.h> /* size_t*/
#include <stdlib.h> /*malloc*/
#include <assert.h>

#include "sorts.h"

#define SHIFT (size_t)10

static void Swap(int *p1, int *p2);
static int FindMax(int *arr, size_t size);
static void CopyArray(int *dest, int *src, size_t size);
static void CountingSortRadix(int *arr, size_t size, size_t radix);

void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	assert(NULL != arr);

	for(i = 0; i < size - 1; ++i)
	{
		for(j = i + 1; j < size; ++j)
		{
			if(arr[i ] >arr[j])
			{
				Swap(arr + i , arr + j);
			}
		}
	}
}
 
void SelectionSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	size_t min_idx = 0;
	
	assert(NULL != arr);

	for(i = 0; i < size - 1; ++i)
	{
		min_idx = i;

		for(j = i + 1; j < size; ++j)
		{
			if(arr[min_idx] > arr[j])
			{
				min_idx = j;
			}
		}
		Swap(arr + i, arr + min_idx);
	}
}

void InsertionSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;

	assert(NULL != arr);

	for(i = 1; i < size; ++i)
	{
		for(j = i; 0 != j && arr[j - 1] > arr[j]; --j)
		{
			Swap(arr + j - 1, arr + j);
		}
	}
}

void CountingSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t temp_arr_size = 0;
    
    int *temp_arr = NULL;
    int *output_arr = NULL;

    int max = 0;

    assert(NULL != arr);

    max = FindMax(arr, size);
    temp_arr_size = max + 1;

   temp_arr = (int *)calloc(temp_arr_size, sizeof(int));
    if (NULL == temp_arr)
    {
        return;
    }

    output_arr = (int *)malloc(sizeof(int) * size);
    if (NULL == output_arr)
    {
        free(temp_arr);
        return;
    }

    for (i = 0; i < size; ++i)
    {
        ++temp_arr[arr[i]];
    }

    for (i = 1; i < temp_arr_size; ++i)
    {
        temp_arr[i] += temp_arr[i - 1];
    }

    for (i = 0; i < size; ++i)
    {
        output_arr[temp_arr[arr[i]] - 1] = arr[i];
        --temp_arr[arr[i]];
    }

    CopyArray(arr, output_arr, size);

    free(temp_arr);
    free(output_arr);
}

void RadixSort(int *arr, size_t size)
{
    size_t i = 0;
    int max = 0;

    assert(NULL != arr);

    max = FindMax(arr, size);

    for (i = 1; (max / (int)i) > 0; i *= SHIFT)
    {
        CountingSortRadix(arr, size, i);        
    }
}

static void CountingSortRadix(int *arr, size_t size, size_t radix)
{
    size_t i = 0;
    int temp_arr[SHIFT] = {0};
    int *output_arr = NULL;

    int curr = 0;

    assert(NULL != arr);

    output_arr = (int *)malloc(sizeof(int) * size);
    if (NULL == output_arr)
    {
        return;
    }

    for (i = 0; i < size; ++i)
    {
        curr = (arr[i] / (int)radix) % SHIFT;
        ++temp_arr[curr];
    }

    for (i = 1; i < SHIFT; ++i)
    {
        temp_arr[i] += temp_arr[i - 1];
    }

    
    
    for (i = size - 1; (int)i >= 0; --i)
    {
		curr = (arr[i] / (int)radix) % SHIFT;
        output_arr[temp_arr[curr] - 1] = arr[i];
        --temp_arr[curr];
    }

    CopyArray(arr, output_arr, size);

    free(output_arr);
}

static void CopyArray(int *dest, int *src, size_t size)
{
    size_t i = 0;
    
	assert(NULL != src);
	assert(NULL != dest);
	
    for (i = 0; i < size; ++i)
    {
        dest[i]= src[i];
    }
}

static int FindMax(int *arr, size_t size)
{
    size_t i = 0;
    int max = 0;
    int curr = 0;

    assert(NULL != arr);

    for (i = 0; i < size; ++i)
    {
        curr = arr[i];
        if (curr > max)
        {
            max = curr;
        }
    }
    return max;
}


static void Swap(int *p1, int *p2)
{
	int temp = 0;
	
	assert(NULL != p1);
	assert(NULL != p2);
	
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

