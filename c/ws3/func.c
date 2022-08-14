#include<stdio.h>
#include<assert.h>
#include <string.h>
#include <stdlib.h>
#include"ws3.h"



void PrintVar()
{
	printf("char: %ld\n", sizeof(char));
	printf("int: %ld\n", sizeof(int));
	printf("float: %ld\n", sizeof(float));
	printf("un int: %ld\n", sizeof(unsigned int));
	printf("size_t: %ld\n", sizeof(size_t));
	printf("long int: %ld\n", sizeof(long int));
	printf("pointer: %ld\n", sizeof(int*));
	printf(" pointer char: %ld\n", sizeof(char*));
}

void PrintArray(int arr[2][3], int x, int y)
{
	int i,j;
	for(i = 0; i < x; i++)
	{
		for(j = 0; j <  y; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n\n");
	}
	printf("\n");

}

void PrintArray_2(int *arr, int x, int y)
{
	int i;
	
	for(i = 0; i < x*y ; ++i)
	{
		printf("%d\t", arr[i]);
		
	}
	printf("\n");
}

void PrintArray_3(int *arr[], int x, int y)
{
	int i,j;
	for(i = 0; i < x; i++)
	{
		for(j = 0; j <  y; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n\n");
	}
	printf("\n");
}

void PrintMatrix(int *arr, int x, int y)
{
	int i;
	for(i = 0; i < x*y ; ++i)
	{
		printf("%d\t", arr[i]);
		
	}
	printf("\n");
}

int *SummArray(int arr[2][3], int x, int y)

{
	int i,j;
	int res;
	int cell;
	int *summ = (int*)malloc(x*(sizeof(int)));
	assert(summ);
	res = 0;
	cell =0;
	
	for(i = 0; i < x; i++)
	{
		for(j = 0; j <  y; j++)
		{
			res+=arr[i][j];
		}
		summ[cell] = res;
		++cell;
		res = 0;
	}
	return summ;
}

char **CreateArrayFromVar(char *env[])
{
	int i;
	char **arr = NULL;
	
	arr = (char**)malloc(50 * sizeof(char *));
	assert(arr);
	assert(env);
	
	for(i = 0; i < 50 || env[i] ; ++i)
	{
		arr[i] = (char*)malloc(strlen(env[i])+1);
		arr[i] = env[i];
			
	}
	for(i = 0; i < 50 ; ++i) printf("%s\n", arr[i] );
	
	return arr;
}

void FreeMemory(char **arr, int len)
{
	int i;
	assert(arr);
	
	for(i = 0; i < len; ++i)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}


int JosesProblem(int arr[], int len)
{
	int i = 0;
	
	arr[len-1] = arr[0];
	
	for(i = 0; i != arr[i]; i = arr[i])
	{
		arr[i] = arr[arr[i]];
		
	}
	
	return i + 1;

}









