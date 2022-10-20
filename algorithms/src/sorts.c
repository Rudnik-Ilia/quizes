
#include <stddef.h> /*size_t*/
#include "sorts.h"


void Swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void InsertionSort(int *arr, size_t size)
{	size_t i = 0;
	size_t j = 0;
	int tmp = 0;
	for(i=1; i < size; i++){
		for(j=i; j>0 && arr[j-1]>arr[j]; j--)
		{

			tmp=arr[j-1];
			arr[j-1]=arr[j];
			arr[j]=tmp;
		}
	}
}

void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
    	for (i = 0; i < size - 1; i++)
    	{
		for (j = 0; j < size - i - 1; j++)
		{
		    if (arr[j] > arr[j + 1])
		    {
		        Swap(&arr[j], &arr[j + 1]);
	            }
		}        
	}

}


void SelectionSort(int *arr, size_t size)
{



}




