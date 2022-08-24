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
#define MAX2(a,b) ((a > b) ? a : b) 
#define MAX3(a,b,c) (a > b) && (a > c)  


int main()
{
	int x = 5;
	float y = 3.14;
	
	SuperStruct* arrayOFstruct[LEN_OF_ARR];
	
	arrayOFstruct[0] = CreaterStruct(INT, &x);
	arrayOFstruct[1] = CreaterStruct(FLOAT, &y);
	arrayOFstruct[2] = CreaterStruct(STR, "Hello");
	
	AddEveryThing(20, arrayOFstruct[0]);
	AddEveryThing(20, arrayOFstruct[1]);
	AddEveryThing(20, arrayOFstruct[2]);
	
	PrintEverything(arrayOFstruct[0]);
	PrintEverything(arrayOFstruct[1]);
	PrintEverything(arrayOFstruct[2]);
	
	Cleaner(arrayOFstruct, LEN_OF_ARR); 
	printf("-------------------------------------\n"); 
	 
	printf("%d\n", MAX2(1,100));
	printf("%d\n", MAX3(1,100,50));
	
	
	   
	
	
	

return 0;
}

