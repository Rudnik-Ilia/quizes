
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"
#include "test.h"


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

void FillArray(int *arr, size_t size)
{
	size_t i = 0;
	
	for(i = 0; i < 5000; ++i)
	{
		arr[i] = rand()%3000;
	}
}

void MesureTime(int *arr, size_t size, void (*func)(int *arr, size_t size))
{
	
	double total_t;
	clock_t start_t;
	clock_t end_t;
	
	start_t = clock();
	
	func(arr, size);
	
	end_t = clock();
	   
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Total time taken by CPU: %f\n", total_t  );
	
	TEST("Test for Insert" , isSorted(arr, size), 1);

}

int main()
{
	int arr[5000] = {0};
	int size = 5000;
	
	
	FillArray(arr, size);
	
	MesureTime(arr, size, BubbleSort);
	
	MesureTime(arr, size, InsertionSort);
	
	
	
	/*
   	double total_t;
	clock_t start_t;
	clock_t end_t;
	
	
	
   	start_t = clock();
    
    
	BubbleSort(arr, size);
	
	end_t = clock();
	   
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Total time taken by CPU: %f\n", total_t  );
	
	TEST("Test for Insert" , isSorted(arr, size), 1);
	*/
	
	

	PASS;
return 0;
}
