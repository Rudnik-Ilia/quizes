#include<stdio.h>/* printf */
#include<assert.h>/* assert */
#include <stdlib.h> /*malloc*/
#include<string.h> /* strlen*/

#include"ws8.h"

#define SIZE_NAME 10
#define BUFF_FOR_3_CASE 50
#define LEN_OF_ARR 3

typedef struct
{
	type name;
    void* data;
    
} SuperStruct;


SuperStruct* CreaterStruct(type nameOf ,void *value)
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
	char* res3 = NULL;
	assert(p_struc);
	
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
		
			res3 =(char*)malloc(BUFF_FOR_3_CASE);
			if(NULL == res3)
			{
				puts("NO MEMORY FOR YOU!SORRY");
			}
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



int main()
{
	int i; 
	int x = 5;
	float y = 3.14;
	
	SuperStruct* arrayOFstruct[LEN_OF_ARR];
	
	arrayOFstruct[0] = CreaterStruct(INT, &x);
	arrayOFstruct[1] = CreaterStruct(FLOAT, &y);
	arrayOFstruct[2] = CreaterStruct(STR, "Hello");
	
	AddEveryThing(10, arrayOFstruct[0]);
	AddEveryThing(10, arrayOFstruct[1]);
	AddEveryThing(10, arrayOFstruct[2]);
	
	PrintEverything(arrayOFstruct[0]);
	PrintEverything(arrayOFstruct[1]);
	PrintEverything(arrayOFstruct[2]);
	   
	   
	   
	
	free(arrayOFstruct[2] -> data);
	for(i = 0; i < LEN_OF_ARR; ++i)
	{
		free(arrayOFstruct[i]);
		arrayOFstruct[i]= NULL;
	}
	
	
	
	











return 0;
}

