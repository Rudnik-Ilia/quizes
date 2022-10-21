
#include <stddef.h> /*size_t*/
#include <assert.h> 
#include <string.h> /*memset*/
#include <stdlib.h> /*malloc*/

#include "sorts.h"


void Swap(int *x, int *y)
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
	
	assert(NULL != arr);
	
	for(i = 0; i < size; ++i)
	{
		for(j = i + 1; j < size; ++j)
		{
			if(arr[i] > arr[j])
			{
				Swap(&arr[j], &arr[i]);
			}
		}
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

	tmp_arr = (int*)malloc(size_of_tmp * sizeof(int));
	res_arr = (int*)malloc(size * sizeof(int));
	
	memset(tmp_arr, 0, size_of_tmp * sizeof(int));
	memset(res_arr, 0, size * sizeof(int));
	

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





















