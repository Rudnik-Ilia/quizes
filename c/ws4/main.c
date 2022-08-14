/**********************
* Title : Worksheet 3 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 16/08/2022
***********************/

#include <ncurses.h> /*getchar compile with flag -lncurses!!!!!!!!!!!!!!!!!!!!!!!!*/
#include<stdio.h> /* printf*/
#include<stdlib.h> /* Malloc */
#include<assert.h> /* Assert */
#include"func.c" /* my functions */
#include"tests.c" /* my tests*/
#include"ws4.h"


typedef void (*p_func)();


int PrintAT_IF()
{
	char x;
	system("stty -icanon -echo");
	
	do
	{
		printf("Insert the char: \n");
		x = getchar();
		
		if('t' == x) printf("T-pressed!\n");
		if('a' == x) printf("A-pressed!\n");
		else printf("Try again!\n");
		
	}
	while(27 != x);
	system("stty icanon echo");
	return 0;
}

int PrintAT_SWITCH()
{
	char x;
	system("stty -icanon -echo");
	printf("Insert the char: \n");
	x = getchar();
	
	do
	{
		printf("Insert the char: \n");
		x = getchar();
		switch(x)
		{
			case 't': 
				printf("T-pressed!\n");
				break;
			case 'a': 
				printf("a-pressed!\n");
				break;
			default:
				printf("Try again!\n");
			
			
		}
	}
	while(27 != x);
	system("stty icanon echo");
	return 0;
}


int main()
{
	
	
	
	
	
	
	





return 0;
}
