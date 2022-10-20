
#include <stddef.h> /*size_t*/
#include <assert.h> 
#include "sorts.h"


void Swap(int *x, int *y)
{
    int temp = *x;
    
    assert(NULL != x);
    assert(NULL != y);
    
    *x = *y;
    *y = temp;
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























