#include <stdio.h>
#include <stdlib.h>


#include "recursion.h"
#include "sorts.h"
#include "test.h"

int Cmp_I(const void *data,const void *sata)
{
	if(*(int*)data <= *(int*)sata)
	{
		return 1;
	}
	else if(*(int*)data > *(int*)sata)
	{
		return 2;
	}
	else
	{
		return 0;
	}	
}

int Cmp_D(const void *data,const void *sata)
{
	if(*(double*)data <= *(double*)sata)
	{
		return 1;
	}
	else if(*(double*)data > *(double*)sata)
	{
		return 2;
	}
	else
	{
		return 0;
	}	
}


int main()
{	
	int arr[] = {1,3,5,7,9,10,26,37,47,58,68,90,100, 104, 300, 333};
	
	int ar[] = {1,3,52,7,999,10,26,370,4,58,6,93,1, 10, 6, 33};
	int ar_sort[] = {1 ,1 ,3 ,4 ,6 ,6 ,7 ,10 ,10 ,26 ,33 ,52 ,58 ,93 ,370 ,999};
	
	double d_arr[] = {50.0, 2.0, 3.0, 100.0, 4.0, 99.0};
	
	size_t i = 0;
	
	size_t size = sizeof(ar)/sizeof(int);
	
	size_t d_size = sizeof(d_arr)/sizeof(double);
	
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
	
	

	QuickSort(ar, size , sizeof(int), Cmp_I);
	
	for(i = 0; i < size; ++i)
	{
		TEST("Merge test", ar[i], ar_sort[i]);
	}
	
	
	QuickSort(d_arr, d_size , sizeof(double), Cmp_D);
	
	
	for(i = 0; i < d_size; ++i)
	{
		printf("%f\n", d_arr[i]);
	}

PASS;
return 0;
}
