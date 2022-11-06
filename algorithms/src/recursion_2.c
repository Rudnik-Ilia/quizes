
#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */


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

