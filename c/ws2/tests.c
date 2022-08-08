#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"string.h"




void test_StrCpy()
{
	char name[] = "Ilia";
	char name_2[4] = "";
	
	

}

void test_StrCmpNum()
{
	char name[] = "Ilia";
	char name_2[4] = "ilia";
	char name_3[310] = "Rudnik";
	
	if(StrCmpNum(name, name_2, 6) == strncmp(name, name_2, 6)) printf("PASS\n");
	if(StrCmpNum(name, name_3, 3) == strncmp(name, name_3, 3)) printf("PASS\n");

}

void test_StrCpyNum()
{

	char dest1[]="11111111111111111111111111111111";
	if (StrCpyNum(dest1, "Hello World!", 5) == strncpy(dest1,"Hello World!",5)) printf("PASS\n");
	
}
void test_StrCaseCmp()
{
	char name[] = "Ilia";
	char name_2[4] = "ilia";
	char name_3[310] = "Rudnik";
	char name_4[] = "rudnik";
	
	if(StrCaseCmp(name, name_2) == strcasecmp(name, name_2)) printf("PASS\n");
	if(StrCaseCmp(name_3, name_4) == strcasecmp(name_3, name_4)) printf("PASS\n");
}






