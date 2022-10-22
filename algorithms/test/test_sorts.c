
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorts.h"
#include "test.h"
#include "utils.h"

#define SIZE_ARRAY 5000
#define RANGE 100


int isSorted(int *arr, size_t size)
{
	size_t i = 0;
	
    	for (i = 0; i < size - 1; i++)
    	{
        	if (arr[i] > arr[i + 1]) 
        	{
        	    return 0;
        	}
    	}	
    return 1;
}

int Comparator(const void * p1, const void * p2)
{
  return (*(int*)p1 - *(int*)p2);
}

void FillArray(int *arr, size_t size, size_t range)
{
	size_t i = 0;
	
	for(i = 0; i < size; ++i)
	{
		arr[i] = rand() % range;
	}
}

float MesureTime(int *arr, size_t size, void (*func)(int *arr, size_t size))
{
	clock_t end_t = 0;
	clock_t start_t = clock();
	
	start_t = clock();
	
	func(arr, size);
	  
	end_t = clock();  
	
	return (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
}

float Time_qsort(int *arr, size_t size, int (*compar)(const void *, const void*))
{
	clock_t end_t = 0;
	clock_t start_t = clock();
	
	start_t = clock();
	
	qsort(arr, size, sizeof(int), compar);
	  
	end_t = clock();  
	
	return (double)(end_t - start_t) / CLOCKS_PER_SEC;;
}

int main()
{
	int arr[SIZE_ARRAY] = {0};
	
	FillArray(arr, SIZE_ARRAY, 3000);
	printf("Time of qsort = %f\n", Time_qsort(arr, SIZE_ARRAY, Comparator));
	TEST("Test for Qsort" , isSorted(arr, SIZE_ARRAY), 1);
	
	FillArray(arr, SIZE_ARRAY, 3000);
	printf("Total time taken by BubbleSort: %f\n", MesureTime(arr, SIZE_ARRAY, BubbleSort));
	TEST("Test for Bubble" , isSorted(arr, SIZE_ARRAY), 1);
	
	FillArray(arr, SIZE_ARRAY, 3000);
	printf("Total time taken by InsertionSort: %f\n", MesureTime(arr, SIZE_ARRAY, InsertionSort));
	TEST("Test for Insert" , isSorted(arr, SIZE_ARRAY), 1);
	
	FillArray(arr, SIZE_ARRAY, 3000);
	printf("Total time taken by SelectionSort: %f\n", MesureTime(arr, SIZE_ARRAY, SelectionSort));
	TEST("Test for Select" , isSorted(arr, SIZE_ARRAY), 1);
	
	FillArray(arr, SIZE_ARRAY, 101);
	printf("Total time taken by CountingSort: %f\n", MesureTime(arr, SIZE_ARRAY, CountingSort));
	TEST("Test for CountSort" , isSorted(arr, SIZE_ARRAY), 1);
	
	FillArray(arr, SIZE_ARRAY, 100);
	printf("Total time taken by RadixSort: %f\n", MesureTime(arr, SIZE_ARRAY, RadixSort));
	TEST("Test for RadixSort" , isSorted(arr, SIZE_ARRAY), 1);
	
	PASS;
return 0;
}
