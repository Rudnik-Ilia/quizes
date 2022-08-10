#include<stdio.h>
#include<assert.h>
#include<string.h>

#include"ws3.h"


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




int main(int argc, char *argv[], char *env[])
{
	/*
	printf("Hello %d\ args: %d\n", argv[1][1], argc);
	int arr[][5] = {1, 2, 3, 4, 5};
	int *p[5] = arr;
	printf("%d", p[2][0]);
	*/
	/*
	int i = 0;
	for(i; env[i];i++);
	if(strstr(env[i], "PATH"))
	{
	printf("%s\n", env[i]);
	}
	
	int i = 0;
	char *name = "ilia";
	
	int arr[][3] = {{1,1,1},{2,2,2},{3,3,3}};
	
	
	int *p = &arr[0][0];
	
	for(i; i< 9; i++){
	
	printf("%d\n", p[i]);
	
	}
	
	printf("%ld\n", sizeof(arr));
	printf("%ld\n", strlen("ilia"));

*/
	
	int arr[2][3] = {{1,8,1},{2,2,9}};
	int *p_arr[2];
	int i;
	
	for(i = 0; i < 2; i++)
	{
		p_arr[i] = arr[i];
	} 
	 
	 PrintArray(arr, 2, 3);
	 
	 
	 PrintArray_2((int*)arr, 2, 3);
	 
	 
	 PrintArray_3(p_arr, 2, 3);


return 0;
}








