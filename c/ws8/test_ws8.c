/**********************
* Title : Worksheet 8 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 28/08/2022
***********************/

#include<stdio.h>/* printf */
#include <stdlib.h> /*free*/

#include"ws8.h"

struct time
{
unsigned int hours: 2; 
unsigned int minutes:30; 
unsigned int seconds:31; 
} time; 



union data
{
   int i;
   float f;
   int d;
   int w;
   char c[8];
   char  str[200];
} data;

int main()
{	int i;
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
	printf("%ld\n", SIZE_OF_VAR(x));
	printf("%ld\n", SIZE_OF_TYPE(char));
	printf("-------------------------------------\n"); 
	data.f = 3.44;
	
	
    
   
    printf( "data.i : %d\n", data.i);
    printf( "data.f : %f\n", data.f);
    printf( "data.w : %d\n", data.d);
   
   
  
    
    printf( "data.str : %s\n", data.str);
   	for(i = 0; i < 20; ++i){
    printf( " %d\n", data.str[i]);
    }
 	 printf( "size : %d\n", SIZE_OF_VAR(time));

	   
	
	
	

return 0;
}

