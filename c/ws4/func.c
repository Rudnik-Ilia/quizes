

#include<stdio.h> /* printf*/
#include<stdlib.h> /* Malloc */
#include<assert.h> /* Assert */
#include"ws4.h"



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



