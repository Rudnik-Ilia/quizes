#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"string.h"


int main()
{	
	 char name[] = "Ilia";
	 char name_2[] = "ilia";
	 char name_3[] = "rudnik";
	 char dest[5];
	 char dest1[]="11111111111111111111111111111111";
	 char dest2[100];
	
	
	//printf("%s - %s - %s\n", StrCpyNum(dest1, "Hello World!", 5), StrCpyNum_2(dest1, "Hello World!", 5), strncpy(dest1,"Hello World!",5));
	
	printf("%d - %d\n", StrCmpNum(name, name_2, 6), strncmp(name, name_2, 6));
	printf("%d - %d\n", StrCmpNum(name, name_3, 3), strncmp(name, name_3, 5));
	
	
	
	
	
	return 0;
}

