


#include <stdio.h>
#include "utils.h"
#include "cbuff.h"



int main()
{	
	char arr[] = {'x', 'b', 'c'};	
	char de[1];
	cbuff_t *buff = CBuffCreate(100);
	
	printf("%d\n", CBuffIsEmpty(buff));
	CBuffWrite(buff, &arr[0] , 1);
	printf("%d\n", CBuffIsEmpty(buff));
	
	CBuffRead(buff, de, 1);
	
	printf("%c\n", de[0]);
	/*
	
	printf("%c\n", buff->capacity));
	

*/



return 0;
}

