
/**********************
* Title : Worksheet 6
* Author: Ilia Rudnik
* Reviewer: 
* Date : 20/08/2022
***********************/


#include<stdio.h> /* printf*/
#include <math.h> /* pow*/
#include"ws6.h"

unsigned long Pow2(unsigned int x, unsigned int y)
{
	
	
return 0;
}


int Pow(int n)
{
	int i;
	int res = 2;
	while(n--)
	{
		res <<= 1;
	}
	return res;

}




int main()
{
	int a;
	int n;
	n = 5;
	a = 2;
	

	printf("%d", a << (n-1));











return 0;
}

