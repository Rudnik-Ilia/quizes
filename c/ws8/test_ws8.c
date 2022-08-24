/**********************
* Title : Worksheet 8 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 28/08/2022
***********************/

#include<stdio.h>/* printf */
#include <stdlib.h> /*free*/
#include"ws8.h"


#define LEN_OF_ARR 3




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

