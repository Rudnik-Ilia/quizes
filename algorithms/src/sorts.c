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
	int max = size; 
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
	
	res_arr = (int*)calloc(size, sizeof(int));
	
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
		tmp_arr[arr[i] - min]--;
	}


	for(i = 0; i < size; ++i)
	{ 
		arr[i] = res_arr[i];
	}


	free(tmp_arr);
	free(res_arr);
}

static void Count(int *arr, int size, int place) {

	int i = 0;
	int freq[10] = {0};
	int *output = NULL;
	
	assert(NULL != arr);
	
	output = (int*)calloc(size, sizeof(int));
	
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












