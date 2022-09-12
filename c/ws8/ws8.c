#include<stdio.h>/* printf */
#include<assert.h>/* assert */
#include <stdlib.h> /*malloc*/
#include<string.h> /* strlen*/

#include"ws8.h"

#define SIZE_NAME 10
#define BUFF_FOR_3_CASE 50
#define LEN_OF_ARR 3



SuperStruct* CreaterStruct(type nameOf ,void *value)
{
    SuperStruct* BigStruct = (SuperStruct*)malloc(sizeof(SuperStruct));
    assert(value); 
    if(NULL == BigStruct)
	{
		puts("NO MEMORY FOR YOU!SORRY");
		return -1;
	}
    BigStruct -> name = nameOf;
    BigStruct -> data = value;
    return BigStruct;
}

void AddEveryThing(int num, SuperStruct* p_struc)
{

	char* buff = NULL;
	assert(p_struc);
	
	switch(p_struc -> name)
	{
		case 1:
		
			*(int*)(p_struc -> data) = *(int*)(p_struc -> data) + num;
			break;
			
		case 2:
			
			*(float*)(p_struc -> data) = *(float*)(p_struc -> data) + (float)num;
			break;
			
		case 3:
		
			buff =(char*)malloc(BUFF_FOR_3_CASE);
			if(NULL == buff)
			{
				puts("NO MEMORY FOR YOU!SORRY");
				return -1;
			}
			sprintf(buff, "%s%d", (char*)(p_struc -> data), num);
			(p_struc -> data) = buff;	
	}
}

void PrintEverything(SuperStruct* p_struc)
{
	assert(p_struc);
	
	switch(p_struc -> name)
	{
		case 1:
		
			printf("%d\n", *(int*)(p_struc -> data));
			break;
		case 2:
		
			printf("%0.2f\n", *(float*)(p_struc -> data));
			break;
		case 3:
		
			printf("%s\n", ((char*)(p_struc -> data)));
			break;
	}
}

void Cleaner(SuperStruct* arr[], int lenArr)
{	
	int i; 
	free(arr[2] -> data);
	
	for(i = 0; i < lenArr; ++i)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
}


