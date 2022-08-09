#include <stdio.h>
#include <malloc.h>


void Swap(int *x,int *y)/* swaping two variable in memory*/
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void SwapSizeT(size_t **x, size_t **y)
{
	int *temp = *x;
    	*x = *y;
    	*y = temp;
	
	
	
}


void CopyArray( int *arr_org, int *arr_copy, int len_of_arr)
{
	int i = 0;
	
	for(i = 0; i < len_of_arr; ++i)
	{
		arr_copy[i]  = arr_org[i];
	}
	
	
	
}

void PrintArr(int arr[], int len_of_arr)
{
	int i = 0;
	for(i = 0; i < len_of_arr; ++i)
	{
		printf("%d", arr[i]);
	}
}



int main()
{
	
	int origin_array[5] = {1,2,3,4,5};
	
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	//int *ptr2 = (int *)malloc(sizeof(int));
	
	unsigned int *ip =0;
	float f = 3;
	float *fp = &f;
	ip = (unsigned int *) fp;
	
	//int *p_arr = (int*)malloc(sizeof(int)*5);
	
	//if (NULL == p_arr)
	//{
		//printf("Trouble!");
	//};
	//free(p_arr);
	//printf("%p\n",&s_i);
	//printf("%p\n",&i);
	//printf("%p\n",&ptr);
	//printf("%p\n",&ptr2);
	
	size_t a = 100;
	size_t b = 200;
	size_t *p_a = &a;
	size_t *p_b = &b;
	
	
	
	
	SwapSizeT(p_a, p_b);
	printf("%ld - %ld\n",p_a,p_b);
	
	//printf("%ld - %ld",a,b);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}


