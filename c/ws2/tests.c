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
void test_StrChar()
 {
 	char x = 'a';
	char y = 'x';
	char name_2[4] = "ilia";
	
 	if(StrChar(name_2, x) == strchr(name_2, x)) printf("PASS\n");
 	if(StrChar(name_2, y) == strchr(name_2, y)) printf("PASS\n");
	
 }
 
void test_StrSpn() 
{
	char word[] = "tyu";
	char f_w[] = "qwertyuiop";
	char bad[] = "xxxxxxxxxxxx";
	
	if (StrSpn(word, f_w) == strspn(word, f_w)) printf("PASS\n"); 
	if (StrSpn(bad, f_w) == strspn(bad, f_w)) printf("PASS\n");   
}

void test_Palindrome()
{
	char word_1[] = "ilia";
	char word_2[] = "ili";
	
	if (0 == Palindrome(word_1)) printf("PASS\n"); 
	if (1 == Palindrome(word_2)) printf("PASS\n"); 
}
 
 





