#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"string.h"


int main()
{	
	 char x = 'a';
	 char y = 'x';
	 char name[] = "Ilia";
	 char name_2[] = "ilia";
	 char name_3[] = "rudnik";
	 char name_4[] = "rudnik";
	 char dest[5];
	 char dest1[]="11111111111111111111111111111111";
	 char dest2[100];
	
	
	//printf("%s - %s - %s\n", StrCpyNum(dest1, "Hello World!", 5), StrCpyNum_2(dest1, "Hello World!", 5), strncpy(dest1,"Hello World!",5));
	
	//printf("%d - %d\n", StrCmpNum(name, name_2, 6), strncmp(name, name_2, 6));
	//printf("%d - %d\n", StrCmpNum(name, name_3, 3), strncmp(name, name_3, 5));
	
	
	//printf("%d - %d\n", StrCaseCmp(name, name_2), strcasecmp(name, name_2));
	//printf("%d - %d\n", StrCaseCmp(name_3, name_4), strcasecmp(name_3, name_4));
	
	
	//printf("%c - %c\n", *StrChar(name_2, x),*strchr(name_2, x));
	printf("%p - %p\n", StrChar(name_2, y),strchr(name_2, y));
	
	
	
	
	
	
	
	
	return 0;
}

