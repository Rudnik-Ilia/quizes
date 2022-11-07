
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorts.h"
#include "test.h"
#include "utils.h"

#define SIZE_ARRAY 5000
#define RANGE 100

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


int isSorted(int *arr, size_t size);
int Comparator(const void * p1, const void * p2);
void FillArray(int *arr, size_t size, size_t range);
float MesureTime(int *arr, size_t size, void (*func)(int *arr, size_t size));
float Time_qsort(int *arr, size_t size, int (*compar)(const void *, const void*));


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
	

	FillArray(arr, SIZE_ARRAY, 100);
	MergeSort(arr, SIZE_ARRAY);
	TEST("Test Mergesort" , isSorted(arr, SIZE_ARRAY), 1);
	
	
	printf("ky ky\n");
	/*
	size_t i = 0;
	int ar[] = {1,3,52,7,999,10,26,370,4,58,6,93,1, 10, 6, 33};
	int ar_sort[] = {1 ,1 ,3 ,4 ,6 ,6 ,7 ,10 ,10 ,26 ,33 ,52 ,58 ,93 ,370 ,999};
	size_t size = sizeof(ar)/sizeof(int);
	
	
	int ar[] = {1,3,52,7,999,10,26,370,4,58,6,93,1, 10, 6, 33};
	size_t size = sizeof(ar)/sizeof(int);
	
	
	double d_arr[] = {50.0, 2.0, 3.0, 100.0, 4.0, 99.0};
	
	size_t i = 0;
	
	
	size_t d_size = sizeof(d_arr)/sizeof(double);	
	
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
	*/
	
	
	
	PASS;
return 0;
}

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

