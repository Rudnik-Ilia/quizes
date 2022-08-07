#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"string.h"


int main()
{	
	
	 char dest[5];
	 char dest1[100];
	 char dest2[100];
	
	
	printf("%s - %s\n", StrCpy(dest, "fffffffffffffffffffffffffffffffffffffffffffffff"), strcpy(dest,"fffffffffffffffffffffffffffffffffffffffffffffff"));
	printf("%s - %s\n", StrCpy(dest1, ""), strcpy(dest1,""));
	printf("%s - %s\n", StrCpy(dest2, "Hello"), strcpy(dest1,"Hello"));
	
	
	
	return 0;
}

