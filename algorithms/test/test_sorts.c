
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorts.h"
#include "test.h"


#define SIZE_ARRAY 5000

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

void FillArray(int *arr, size_t size)
{
	size_t i = 0;
	
	for(i = 0; i < size; ++i)
	{
		arr[i] = rand() % size;
	}
}

void MesureTime(int *arr, size_t size, void (*func)(int *arr, size_t size))
{
	
	double total_t = 0;
	clock_t end_t = 0;
	clock_t start_t = clock();
	
	start_t = clock();
	
	func(arr, size);
	  
	end_t = clock();  
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	printf("Total time taken by CPU: %f\n", total_t  );
	
	TEST("Test for Insert" , isSorted(arr, size), 1);
}

int main()
{
	int arr[SIZE_ARRAY] = {0};
	
	FillArray(arr, SIZE_ARRAY);
	
	MesureTime(arr, SIZE_ARRAY, BubbleSort);
	
	FillArray(arr, SIZE_ARRAY);
	
	MesureTime(arr, SIZE_ARRAY, InsertionSort);
	
	FillArray(arr, SIZE_ARRAY);
	
	MesureTime(arr, SIZE_ARRAY, SelectionSort);
	
	FillArray(arr, SIZE_ARRAY);
	
	qsort(arr, SIZE_ARRAY, 4, Comparator);
	
	TEST("Test for Insert" , isSorted(arr, SIZE_ARRAY), 1);
	
	
	
	

	PASS;
return 0;
}
