
/**********************
* Title : Worksheet 8,5 
* Author: Ilia Rudnik
* Reviewer: Kate
* Date : 28/08/2022
* Status : 
***********************/

#include <stdio.h>

#include "ws9.h"

#define SIZE_ARRAY 23


void Test_MemSet();
void Test_MemCpy();
void Test_MemMove();

int main()
{

	Test_MemMove();
	Test_MemSet();
	Test_MemCpy();
	
	return 0;
}


void Test_MemSet()
{	
	char arr[SIZE_ARRAY] = "OOOOOOOOOOOOOOOOOOOO";
	printf("String before set: OOOOOOOOOOOOOOOOOOOO\n");
	MemSet(arr, '$', 10);
	printf("String after set - %s\n",arr);
	printf("***********************************************\n");	
}

void Test_MemCpy()
{	
	char arr[SIZE_ARRAY] = "Hello I am new array";
	char arr2[SIZE_ARRAY];
	printf("String before copy: Hello I am new array\n");
	MemCpy(arr2, arr, SIZE_ARRAY);
	
	printf("String after copy: %s\n",arr2);
	printf("***********************************************\n");	
		
}

void Test_MemMove()
{
	char dest[30] = "abcdef";
	char src[] = "*****";
    printf("String before move: %s\n",dest);
    MemMove(dest,dest+1,3);
    printf("String after move: %s\n",dest);
    printf("***********************************************\n");
    printf("String before move: %s\n",dest);
    MemMove(dest,src,4);
    printf("String after move: %s\n",dest);
    printf("***********************************************\n");	
    printf("String before move: %s\n",dest);
    MemMove(dest,dest,5);
    printf("String after move: %s\n",dest);
    printf("***********************************************\n");
}








