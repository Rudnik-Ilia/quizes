#include <stdio.h>

#include "recursion.h"
#include "test.h"
/*
ssize_t bisearch(int *arr, int value_to_find, int min, int max)
{
	int midpoint = ( min + max ) / 2;  
	if (max < min)
	{
		return -1;
	}
	if (arr[midpoint] > value_to_find)
	{
	 	return bisearch(arr, value_to_find, min, midpoint - 1);
	}	 
	if (arr[midpoint] < value_to_find)
	{
		return bisearch(arr, value_to_find, midpoint + 1, max);
	}
	if (value_to_find == arr[midpoint])
	{
		return midpoint;
	}
	return -1;
}
*/
int main()
{	
	int arr[] = {1,3,5,7,9,10,26,37,47,58,68,90,100, 104, 300, 333};
	
	size_t size = sizeof(arr)/sizeof(int);
	
	TEST("Iter", BinarySearchIter(arr,size, 68), 10);
	TEST("Iter", BinarySearchIter(arr,size, 1), 0);
	TEST("Iter", BinarySearchIter(arr,size, 333), 15);
	TEST("Iter", BinarySearchIter(arr,size, 7), 3);
	TEST("Iter", BinarySearchIter(arr,size, 90), 11);
	TEST("Iter", BinarySearchIter(arr,size, 11111), -1);
	TEST("Iter", BinarySearchIter(arr,size, 2), -1);
	
	
	TEST("Recur", BinarySearchRec(arr, size, 68), 10);
	TEST("Recur", BinarySearchRec(arr, size, 1), 0);
	TEST("Recur", BinarySearchRec(arr, size, 333), 15);
	TEST("Recur", BinarySearchRec(arr, size, 7), 3);
	TEST("Recur", BinarySearchRec(arr, size, 90), 11);
	TEST("Recur", BinarySearchRec(arr, size, 11111), -1);
	TEST("Recur", BinarySearchRec(arr, size, 2), -1);
	
	
	
	
	/*
*/
PASS;
return 0;
}
