/**********************
* Title : Worksheet 3 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 16/08/2022
***********************/

#include <ncurses.h>
#include<stdio.h> /* printf*/
#include<stdlib.h> /* Malloc */
#include<assert.h> /* Assert */
#include"func.c" /* my functions */
#include"tests.c" /* my tests*/

#include"ws4.h"


void hello()
{
	printf("Hello");
}

int he(int x, int y)
{
	return x*y;
}


int main()
{

	int (*message) (int, int);
     
    message=he;
    printf("%d\n",message(3,5));






return 0;
}
