#include<stdio.h>
#include<assert.h>
#include<string.h>

#include"ws3.h"


void PrintArray(int *arr, int x, int y)
{
	int i;
	int len = y*x;
	int *ptr = &arr[0];
	
	for(i= 0 ; i < len; ++i)
	{
		if(i == y) printf("\n\n");
		printf("%d\t", ptr[i]);
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
	int arr[2][4] = {{1,8,1,4},{2,2,9,4}};
	
	 
	 PrintArray(arr[0], 2, 4);


return 0;
}








