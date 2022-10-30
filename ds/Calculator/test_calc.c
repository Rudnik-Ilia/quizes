#include <stdio.h>

#include "calc.h"


int main()
{	
	double *res = NULL;

	InfixToPost("2+8 ",res , 4);
	InfixToPost("8+8 ",res , 4);
	InfixToPost("0+5 ",res , 4);
	InfixToPost("1+7 ",res , 4);

	
return 0;
}
