
#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */
#include <stdlib.h>



static ssize_t Bisearch(int *arr, int value_to_find, int min, int max)
{
	int middle = ( min + max ) / 2;  
	if (max < min)
	{
		return -1;
	}
	if (arr[middle] > value_to_find)
	{
	 	return Bisearch(arr, value_to_find, min, middle - 1);
	}	 
	if (arr[middle] < value_to_find)
	{
		return Bisearch(arr, value_to_find, middle + 1, max);
	}
	if (value_to_find == arr[middle])
	{
		return middle;
	}
	return -1;
}

ssize_t BinarySearchIter(int *arr, size_t size, int value_to_find)
{
	int min = 0;
	int max = size-1;
	int middle = 0;
	
	while(1)
	{	
		middle = (min + max)/2;
		
		if(value_to_find > arr[middle])
		{
			min = middle + 1;
		}
		else if(value_to_find < arr[middle])
		{
			max = middle - 1;
		}
		else 
		{
			return middle;
		}
		if(min > max)
		{
			return -1;
		}
	}

}


ssize_t BinarySearchRec(int *arr, size_t size, int value_to_find)
{
	return Bisearch(arr, value_to_find, 0, size);
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	size_t i = 0;
	size_t li = 0;
	size_t ri = 0;

	size_t sizeleft = num_elements / 2;
	size_t sizeright = num_elements - sizeleft;
	
	int *left = malloc(sizeleft * sizeof(int));
	int *right= malloc(sizeright * sizeof(int));

	if(num_elements == 1)
	{
		return 0;
	}

	li = 0;
	ri = 0;
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
	
	for(i = 0; i<num_elements; i++)
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
	free(left);
	free(right);
	return 0;

}

