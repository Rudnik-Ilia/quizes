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


void Print()
{
	printf("%d\n", 777);
}




int main()
{

	struct father
	{
		int point;
	
		p_func *PrintMe;
	};


	
	struct father print_me;
	
	print_me.point = 5;
	*print_me.PrintMe = &Print;
	
	*print_me.PrintMe();
	printf("%d\n", print_me.point );


















return 0;
}

