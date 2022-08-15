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

/*just empty func*/
void Function()
{
	
}

/* special function for printing*/
void SpecialFuncA()
{
	printf("A-pressed!\n");
}
void SpecialFuncB()
{
	printf("B-pressed!\n");
}
void SpecialFuncQ()
{
	system("stty icanon echo");
	exit(0);
}


/* fill an empty array by func_pointers*/
p_func *FillArray(p_func arrayFunc[], p_func func)
{
	int i = 0;
	
	for(i = 0; i < 256; ++i)
	{
		arrayFunc[i] = func;
	}
	
	return arrayFunc;
}

/* fill an not empty array by special functions*/
p_func *FillArraySpecial(p_func arrayFunc[], p_func func, int num)
{
	arrayFunc[num] = func;
	return arrayFunc;
}


int test(p_func arrayFunc[])
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
			case 'b': 
				arrayFunc[97]();
				break;
			case 'a': 
				arrayFunc[98]();
				break;
			case 'q': 
				arrayFunc[113]();
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
	
	int i;
	
	p_func arrayFunc[256];
	FillArray(arrayFunc, &Function);
	FillArraySpecial(arrayFunc, &SpecialFuncA, 97);
	FillArraySpecial(arrayFunc, &SpecialFuncB, 98);
	FillArraySpecial(arrayFunc, &SpecialFuncQ, 113);
	
	test(arrayFunc);
	
	
	
	
	
	
	
	
	
	
	/*
	for(i = 0; i < 256; ++i) printf("%p\n", arrayFunc[i]);
	*/
	
	
	
	
	
	
	
	





return 0;
}
