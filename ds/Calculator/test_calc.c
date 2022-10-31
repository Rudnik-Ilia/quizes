#include <stdio.h>

#include "calc.h"


int main()
{	
	double *res = NULL;
	/*
	InfixToPost("9*8=",res ,4);
	InfixToPost("3+3=",res ,4);
	InfixToPost("9/8=",res ,4);
	InfixToPost("2-1=",res ,4);
	InfixToPost("2^6=",res ,4);
	*/
	InfixToPost("2+6+3+7+6+8+5+3+7+8+9+6+9+2=",res ,25);
	

	
return 0;
}
