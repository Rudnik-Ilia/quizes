/**********************
* Title : Worksheet 8,5 
* Author: Ilia Rudnik
* Reviewer: Alena
* Date : 28/08/2022
* Status : approved)
***********************/
#include<stdio.h>/* printf */
#include <stdlib.h> /*free*/
#include <string.h> /* strlen */

#include"ws8_5.h"

#define SIZE_NAME 20
#define SIZE_SONAME 20

#pragma pack(1) 



void TestForSerial(student* a, student* b);

int main()
{
	student* First = calloc(1, sizeof(student));
	student* Second = calloc(1, sizeof(student));
	
	memcpy(First -> name, "Ilia",SIZE_NAME);
	memcpy(First -> soname, "Rudnik",SIZE_SONAME);
	First -> grades.human.a = 3.14;
	First -> grades.real.b = 99.99;
	First -> grades.sport = 100.0;
	
	Writer(First);
	Reader(Second);
	
	/*	
	printf("%s\n", First -> name);
	printf("%s\n", First -> soname);
	printf("%f\n", First -> grades.human.a);
	printf("%f\n", First -> grades.real.b);
	printf("%f\n", First -> grades.sport);
		
	printf("%s\n", Second -> name);
	printf("%s\n", Second -> soname);
	printf("%f\n", Second -> grades.human.a);
	printf("%f\n", Second -> grades.real.b);
	printf("%f\n", Second -> grades.sport);
	*/
	TestForSerial(First, Second);
	
	free(First);
	free(Second);

return 0;
}

void TestForSerial(student* a, student* b)
{
	printf("Test for SERIALIZATION : ");
	if(!strcmp(a -> name, b -> name) && !strcmp(a -> soname, b -> soname) \
	&& a -> grades.human.a == b -> grades.human.a\
	&& a -> grades.real.b == b -> grades.real.b\
	&& a -> grades.sport == b -> grades.sport)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
	} 
}
