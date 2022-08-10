#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include"string.h"

char *strdup(const char *x);


void test_StrCpy()
{
	char name_7[10] = "";
	if(StrCpy("ilia", name_7) == strcpy("ilia", name_7)) printf("PASS\n");
	if(StrCpy("Rudnik", name_7) == strcpy("Rudnik", name_7)) printf("PASS\n");
}

void test_StrCmpNum()
{
	char name[] = "Ilia";
	char name_2[4] = "ilia";
	char name_3[310] = "Rudnik";
	printf("Test StrCnpNum\n");
	if(StrCmpNum(name, name_2, 6) == strncmp(name, name_2, 6)) printf("PASS\n");
	if(StrCmpNum(name, name_3, 3) == strncmp(name, name_3, 3)) printf("PASS\n");

}

void test_StrCpyNum()
{
	char dest1[]="11111111111111111111111111111111";
	printf("Test StrCpyNum\n");
	if (StrCpyNum(dest1, "Hello World!", 5) == strncpy(dest1,"Hello World!",5)) printf("PASS\n");
	if (StrCpyNum(dest1, "H", 5) == strncpy(dest1,"H",5)) printf("PASS\n");
}
void test_StrCaseCmp()
{
	char name[] = "Ilia";
	char name_2[4] = "ilia";
	char name_3[310] = "Rudnik";
	char name_4[] = "rudnik";
	printf("Test StrCaseCmp\n");
	if(StrCaseCmp(name, name_2) == strcasecmp(name, name_2)) printf("PASS\n");
	if(StrCaseCmp(name_3, name_4) == strcasecmp(name_3, name_4)) printf("PASS\n");
}
void test_StrChar()
 {
 	char x = 'a';
	char y = 'x';
	char name_2[4] = "ilia";
	printf("Test StrChar\n");
 	if(StrChar(name_2, x) == strchr(name_2, x)) printf("PASS\n");
 	if(StrChar(name_2, y) == strchr(name_2, y)) printf("PASS\n");
 }
 
 
void test_StrCatNum()
{
	char one[] = "wwwwwwww";
	char two[] = "dddd";
	char tree[100] = "g";
	printf("Test StrCatNum\n");
	if(StrCatNum(tree, one, 4) == strncat(tree, one, 4)) printf("PASS\n");
 	if(StrCatNum(tree, two, 3) == strncat(tree, two, 3)) printf("PASS\n");
} 

 
void test_StrSpn() 
{
	char word[] = "tyu";
	char f_w[] = "qwertyuiop";
	char bad[] = "xxxxxxxxxxxx";
	printf("Test StrSpn\n");
	if (StrSpn(word, f_w) == strspn(word, f_w)) printf("PASS\n"); 
	if (StrSpn(bad, f_w) == strspn(bad, f_w)) printf("PASS\n");   
}

void test_Palindrome()
{
	char word_1[] = "ilia";
	char word_2[] = "illi";
	printf("Test Palindrome\n");
	if (0 == Palindrome(word_1)) printf("PASS\n"); 
	if (1 == Palindrome(word_2)) printf("PASS\n"); 
}

void test_StrStr()
{
	char name[] = "Ilia";
	char sentence[] = "Who nows Ilia?";
	printf("Test StrStr\n");
	if(StrStr(sentence, name) == strstr(sentence, name)) printf("PASS\n");	
}

void test_StrCat()
{
	char name_3[310] = "Rudnik";
	char name[] = "Ilia";
	printf("Test Strcat\n");
	if(*StrCat(name_3, name) == *strcat(name_3, name) && *(StrCat(name_3, name)+9) == *(strcat(name_3, name) + 9)) printf("PASS\n");
	if(*StrCat_2(name_3, name) == *strcat(name_3, name) && *(StrCat_2(name_3, name)+9) == *(strcat(name_3, name) + 9)) printf("PASS\n");
}


void test_StrDup()
{
	
	
	char *p_1 = strdup("ilia");
	char *p_2 = strdup("hooo");
	char *ppp = StrDup("ilia");
	char *ppp_1 = StrDup("hooo");
	
	
	printf("Test StrDup\n");
	
	
	
	if (!strcmp(ppp, p_1)) printf("PASS\n");
	if (!strcmp(ppp_1, p_2)) printf("PASS\n");
	
	free(p_1);
	free(p_2);
	free(ppp);
	free(ppp_1);
	
	
	
	

}	

void test_Boom()
{
	

}
 
 





