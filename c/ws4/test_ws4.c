/**********************
* Title : Worksheet 3 
* Author: Ilia Rudnik
* Reviewer: Maria
* Review status:
* Date : 16/08/2022
***********************/


#include<stdio.h> /* printf*/
#include <stdlib.h> /*system*/
#include"ws4.h"


/* test for A and B! Q - is exit*/
int test(p_func arrayFunc[])
{
	char x;
	system("stty -icanon -echo");
	
	do
	{
		printf("Insert the char: \n");
		x = getchar();
		switch(x)
		{
			case 'b': 
				arrayFunc[98]();
				break;
			case 'a': 
				arrayFunc[97]();
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
	
	
	p_func arrayFunc[256];
	FillArray(arrayFunc, &Function);
	FillArraySpecial(arrayFunc, &SpecialFuncA, 97);
	FillArraySpecial(arrayFunc, &SpecialFuncB, 98);
	FillArraySpecial(arrayFunc, &SpecialFuncQ, 113);
	test(arrayFunc);
	

return 0;
}
