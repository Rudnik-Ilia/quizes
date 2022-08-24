#include<stdio.h>/* printf */
#include<assert.h>/* assert */
#include <stdlib.h> /*malloc*/
#include<string.h> /* strlen*/

#include"ws8.h"

#define SIZE_NAME 10
#define BUFF_FOR_3_CASE 50





typedef struct
{
	int name;
    void* data;
    
} SuperStruct;


SuperStruct* CreaterStruct(int nameOf ,void *value)
{
    SuperStruct* BigStruct = (SuperStruct*)malloc(sizeof(SuperStruct));
    assert(value); 
    if(NULL == BigStruct)
	{
		puts("NO MEMORY FOR YOU!SORRY");
	}
    BigStruct -> name = nameOf;
    BigStruct -> data = value;
    return BigStruct;
}

void AddEveryThing(int num, SuperStruct* p_struc)
{

	int res;
	float res2;
	char *res3 =(char*)malloc(BUFF_FOR_3_CASE);
	assert(p_struc);
	if(NULL == res3)
	{
		puts("NO MEMORY FOR YOU!SORRY");
	}
	switch(p_struc -> name)
	{
		case 1:
			
			res = *(int*)(p_struc -> data);
			res += num;
			*(int*)(p_struc -> data) = res;
			break;
			
		case 2:
		
			res2 = *(float*)(p_struc -> data);
			res2 += (float)num;
			*(float*)(p_struc -> data) = res2;
			break;
			
		case 3:
		
			sprintf(res3, "%s%d", (char*)(p_struc -> data), num);
			(p_struc -> data) = res3;					
			
	}
}

void PrintEverything(SuperStruct* p_struc)
{
	assert(p_struc);
	
	switch(p_struc -> name)
	{
		case 1:
		
			printf("%d", *(int*)(p_struc -> data));
			break;
		case 2:
		
			printf("%f", *(float*)(p_struc -> data));
			break;
		case 3:
		
			printf("%s\n", ((char*)(p_struc -> data)));
			break;
	}
}



int main()
{
	
	int x = 5;
	float y = 3.14;
	
	
	
	SuperStruct* arrayOFstruct[3];
	
	arrayOFstruct[0] = CreaterStruct(1, &x);
	arrayOFstruct[1] = CreaterStruct(2, &y);
	arrayOFstruct[2] = CreaterStruct(3, "Hello");
	
	/*
	char string[BUFF_FOR_3_CASE] = "Hello";
	printf("%s\n", arrayOFstruct[2] -> name);
	printf("%c\n", *(char*)(arrayOFstruct[2] -> data));
	*/
	
	AddEveryThing(255, arrayOFstruct[2]);
	/*
	printf("%f\n", *(float*)(arrayOFstruct[1] -> data));
	AddEveryThing(10, arrayOFstruct[1]);
	printf("%f\n", *(float*)(arrayOFstruct[2] -> data));
	for(i = 0; i < 10; ++i){
		
		printf("%c\n", ((char*)(arrayOFstruct[2] -> data))[i]);
	}
	*/
	PrintEverything(arrayOFstruct[2]);
	
	
	
	
	











return 0;
}

