#include <stdio.h>
#include <stdlib.h>

#include "recursion.h"
#include "sorts.h"
#include "test.h"


/*
int Mergesort(int array[], int length)
{
	int i = 0;
	int li = 0;
	int ri = 0;

	int sizeleft = length / 2;
	int sizeright = length - sizeleft;
	
	int *left = malloc(sizeleft * sizeof(int));
	int *right= malloc(sizeright * sizeof(int));

	if(length == 1)
	{
		return 0;
	}

	li = 0;
	ri = 0;
	for(i = 0; i < length; ++i)
	{
		if(i < sizeleft)
		{
			left[li] = array[i];
			li++;
		}
		else
		{
			right[ri] = array[i];
			ri++;
		}
	}


	Mergesort(left, sizeleft);
	
	Mergesort(right, sizeright);


	li = 0;
	ri = 0;
	
	for(i = 0;i<length;i++)
	{
		if((left[li] <= right[ri] && li < sizeleft) || ri == sizeright)
		{
			array[i] = left[li];
			li++;
		}
		else
		{
			array[i] = right[ri];
			ri++;
		}
	}
	return 0;

}


*/


int main()
{	
	int arr[] = {1,3,5,7,9,10,26,37,47,58,68,90,100, 104, 300, 333};
	int ar[] = {1,3,52,7,999,10,26,370,4,58,6,93,1, 10, 6, 33};
	size_t i = 0;
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
	
	MergeSort(ar, 16);
	
	for(i = 0; i < size; ++i)
	{
		printf("%d ", ar[i]);
	}
	
	
	/*
*/
PASS;
return 0;
}
