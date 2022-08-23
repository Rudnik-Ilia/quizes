#include<stdio.h>/* printf */
#include<assert.h>/* assert */
#include <stdlib.h> /*malloc*/


#include"ws8.h"


#define SIZE_NAME 10



typedef int (*p_to_action)(const char*,const char*);

typedef struct
{
	int name;
    void* data;
    
} SuperStruct;


SuperStruct* CreaterStruct(int nameOf ,void *value)
{
    SuperStruct* BigStruct = (SuperStruct*)malloc(sizeof(SuperStruct));
    
    assert(BigStruct);
    
    BigStruct -> name = nameOf;
    BigStruct -> data = value;
    
    return BigStruct;
}

void AddEveryThing(int num, SuperStruct* p_struc)
{
	int res;
	float res2;
	res = 0;
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
			
			
		default:
			printf("Error\n");
		
				
	}
}



int main()
{
	int x = 5;
	float y = 3.14;
	
	
	SuperStruct* arrayOFstruct[3];
	
	arrayOFstruct[0] = CreaterStruct(1, &x);
	arrayOFstruct[1] = CreaterStruct(2, &y);
	arrayOFstruct[2] = CreaterStruct(3, "hello");
	
	/*
	printf("%s\n", arrayOFstruct[2] -> name);
	printf("%c\n", *(char*)(arrayOFstruct[2] -> data));
	*/
	AddEveryThing(10, arrayOFstruct[1]);
	printf("%f\n", *(float*)(arrayOFstruct[1] -> data));
	AddEveryThing(10, arrayOFstruct[1]);
	printf("%f\n", *(float*)(arrayOFstruct[1] -> data));

	
	
	
	
	











return 0;
}

