/**********************
* Title : Worksheet 8,5 
* Author: Ilia Rudnik
* Reviewer: Olga
* Date : 01/09/2022
* Status : 
***********************/
#include <stdio.h> /* printf*/
#include <stdlib.h> /*malloc*/
#include <string.h> /* strlen */
#include <assert.h> /* assert*/

#include "ws10.h"

#define INDIAN (*(unsigned int*)"\0\xff" > 0x100)

void Test_Macro();
void Test_ItoaBase36();
void Test_AtoiBase36();
void Test_ItoaBase10();
void Test_AtoiBase10();
void Test_PrintCommonForTwo();
void Test_IsLittleEndian();


int main()
{	
	Test_Macro();
	Test_ItoaBase36();
	Test_AtoiBase36();
	Test_ItoaBase10();
	Test_AtoiBase10();
	Test_PrintCommonForTwo();
	Test_IsLittleEndian();
	
	
	
	
return 0;
}
void Test_Macro()
{
	puts("Test for Test_Macro");
	if (1 == INDIAN)
	{
		puts("PASS");
	}
	else
	{
		puts("FAIL");
	}
	puts("=======================================");

}





void Test_ItoaBase36()
{
	int num = -1379;
	char* buff = (char*)malloc(HelperCount36(num, 2)+1);
	if(NULL == buff)
	{
		
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	puts("Test for ItoaBase36");
	
	ItoaBase36(num, buff, 2);
	if(!strcmp(buff, "10101100011"))
	{
		puts("PASS");
	}
	else
	{
		puts("FAIL");
	}
	puts("=======================================");
	free(buff);
	
	

}


void Test_AtoiBase36()
{	
	puts("Test for AtoiBase36");
	if(AtoiBase36("1111000", 2) == 120 && AtoiBase36("56AF", 140400))
	{
		puts("PASS");
	}
	else
	{
		puts("FAIL");
	}	
	puts("=======================================");

}



void Test_ItoaBase10()
{	
	int num = -1234;
	char* buff = (char*)malloc(HelperCount(num)+1);
	if(NULL == buff)
	{
		
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}
	puts("Test for ItoaBase10");
	ItoaBase10(num, buff);
	puts(buff);
	if(!strcmp(buff, "1234"))
	{
		puts("PASS");
	}
	else
	{
		puts("FAIL");
	}
	puts("=======================================");
	free(buff);
}

void Test_AtoiBase10()
{
	puts("Test for AtoiBase10");
	
	if(AtoiBase10("134") == 134 && AtoiBase10("1w2") == 0)
	{
		puts("PASS");
	}
	else
	{
		puts("FAIL");
	}
	
	puts("=======================================");


}



void Test_IsLittleEndian()
{
	puts("Test for IsLittleEndian");
	if (1 == IsLittleEndian())
	{
		puts("PASS");
	}
	else
	{
		puts("FAIL");
	}
	puts("=======================================");

}



void Test_PrintCommonForTwo()
{	
	char arr1[] = {'A','B','C','D'};
	char arr2[] = {'A','B','C','D'};
	char arr3[] = {'C', 'E', 'M', 'N'};
	puts("Test for PrintCommonForTwo: ");
	printf("ABCD - ABCD - CEMN\n");
	printf("Answer :");
	PrintCommonForTwo(arr1, arr2, arr3, 4, 4, 4);
	puts("=======================================");
}












