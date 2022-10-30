#include <stdio.h>

#include "calc.h"


int main()
{	
	double *res = NULL;
	InfixToPost("2+1 ",res ,4);
	InfixToPost("2-1 ",res ,4);
	InfixToPost("9*8 ",res ,4);
	InfixToPost("9/8 ",res ,4);
	
	InfixToPost("3^3 ",res , 4);
	

	
return 0;
}
