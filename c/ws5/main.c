/**********************
* Title : Worksheet 5 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 16/08/2022
***********************/


#include<stdio.h> /* printf*/
#include<stdlib.h> /* Malloc */
#include<assert.h> /* Assert */
#include"ws5.h"


typedef void (*p_func)(int);


typedef struct
{
    int number;
    p_func PrintMe;
    
} myStruct;


void Print(int number)
{
	printf("%d\n", number);
}

myStruct* creater(int a, p_func func)
{
    myStruct *print_me = (myStruct*)malloc(sizeof(myStruct));
    assert(print_me);
    print_me -> number = a;
    print_me -> PrintMe = func;
    return print_me;
}



int main()
{	
	int i;
	myStruct *arrayOFstruct[10];
	
	for(i = 0; i < 10; ++i)
	{
		arrayOFstruct[i] = creater((i+1), Print);
	}
	
	for(i = 0; i < 10; ++i)
	{
		arrayOFstruct[i] -> PrintMe(i);
	}
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	


















return 0;
}

