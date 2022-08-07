#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"string.h"


int main()
{	
	
	 char dest[5];
	 char dest1[]="11111111111111111111111111111111";
	 char dest2[100];
	
	
	printf("%s - %s - %s\n", StrCpyNum(dest1, "Hello World!", 5), StrCpyNum_2(dest1, "Hello World!", 5), strncpy(dest1,"Hello World!",5));
	
	
	
	
	
	
	
	return 0;
}

