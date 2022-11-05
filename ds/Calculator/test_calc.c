#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 #include <alloca.h>
#include "calc.h"




int main()
{	
	double *res = NULL;
	
	
	/*
	MainFunc("9*8=",res ,4);
	MainFunc("9/8=",res ,4);
	MainFunc("20*3+(12+71)*2+45+1=",res ,5);
	MainFunc("2+6+3+7+6+8+5+3+7+8+9+6+9+2=",res ,25);
	MainFunc("(4+4)*(2-5)*2=",res ,20);
	MainFunc("((2-5)*2)/3=",res ,20);
	MainFunc("2^6=",res ,10);
	MainFunc("((4+3)*(2+4))*3=",res ,16);
	MainFunc("(-2)+(-5)=",res ,10);
	MainFunc("(2^(2^3))*5=",res ,10);
	MainFunc("((5*2)*2+(2+2)*2+3*(9-2))/2 =",res ,30);
	
	

	MainFunc("(((2000 + -300)-100/3)^2)/33=", res, 10);
	*/
	Calculate("((2000 + (-300)-100/3)^2)/33=",res);
	

	

	
	
  
	
return 0;
}
