/**********************
* Title : Worksheet 8 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 28/08/2022
***********************/
#include<stdio.h>/* printf */
#include <stdlib.h> /*free*/

#include"ws8_5.h"

#pragma pack(1) 

typedef struct
{
	float lit;
	float lang;
	
}human_grades;

typedef struct
{
	float phis;
	float math;

}real_grades;

typedef struct
{
	human_grades Human;
	real_grades Real;
	float grades;
}grades;

typedef struct
{
	char* name;
	char* soname;
	grades Grades;
	
}student;





int main()
{

	printf("%d\n", sizeof(student));






return 0;
}
