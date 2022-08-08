#include<stdio.h>
#include<assert.h>
#include<string.h>

#include"string.h"


void test_StrCmpNum();
void test_StrCpyNum();
void test_StrCaseCmp();

int main()
{	
	 char x = 'a';
	 char y = 'x';
	 char name[] = "Ilia";
	 char name_emp[10];
	 char name_2[4] = "ilia";
	 char name_3[310] = "Rudnik";
	 char name_4[] = "rudnik";
	 char dest[5];
	 char dest1[]="11111111111111111111111111111111";
	 char dest2[100];
	 char sentence[] = "Who nows Ilia?";
	 char * p_name = name;
	
	//test_StrCmpNum();
	//test_StrCpyNum();
	//test_StrCaseCmp();
	
	//printf(StrCpy(name, name_emp));
	//printf(strcpy(name, name_emp));
	
	
	
	
	
	
	
	//printf("%c - %c\n", *StrChar(name_2, x),*strchr(name_2, x));
	//printf("%p - %p\n", StrChar(name_2, y),strchr(name_2, y));
	
	
	//printf("%c - %c\n", *StrDup(name), *strdup(name));
	//printf("%c - %c\n", *StrDup(name_4), *strdup(name_4));
	
	
	
	
	/*
	if(*StrCat(name_3, name) == *strcat(name_3, name) && *(StrCat(name_3, name)+9) == *(strcat(name_3, name) + 9))
	{
		printf("PASS\n");
	};
	
	if(*StrCat_2(name_3, name) == *strcat(name_3, name) && *(StrCat_2(name_3, name)+9) == *(strcat(name_3, name) + 9))
	{
		printf("PASS\n");
	};
	*/
	
	//printf("%p - %p\n", StrStr(sentence, name), strstr(sentence, name));

	
	
	
	
	
	return 0;
}





