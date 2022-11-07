
#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */
#include <alloca.h>
#include <stdlib.h>
#include <assert.h>

#include <string.h>


static ssize_t _bisearch(int *arr, int value_to_find, int min, int max)
{
	int middle = ( min + max ) / 2;  
	if (max < min)
	{
		return -1;
	}
	if (arr[middle] > value_to_find)
	{
	 	return _bisearch(arr, value_to_find, min, middle - 1);
	}	 
	if (arr[middle] < value_to_find)
	{
		return _bisearch(arr, value_to_find, middle + 1, max);
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
	return _bisearch(arr, value_to_find, 0, size);
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	size_t i = 0;
	size_t li = 0;
	size_t ri = 0;

	size_t sizeleft = num_elements / 2;
	size_t sizeright = num_elements - sizeleft;
	
	int *left = alloca(sizeleft * sizeof(int));
	int *right= alloca(sizeright * sizeof(int));

	li = 0;
	ri = 0;	
	
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







