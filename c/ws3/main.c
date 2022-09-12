/**********************
* Title : Worksheet 3 
* Author: Ilia Rudnik
* Reviewer: 
* Date : 13/08/2022
***********************/


#include<stdio.h> /* printf*/
#include<stdlib.h> /* Malloc */
#include<assert.h> /* Assert */
#include"ws3.h"





void Test_SummArray();
void Test_Joses();
void Test_PrintVar();


int main()
{
	
	
	Test_SummArray();

	return 0;
}


void Test_SummArray()
{
	int arr[2][3] = {{1,2,3},{4,5,6}};
	
	if(SummArray(*arr, 2, 3)[1] == 15 && SummArray(*arr, 2, 3)[0] == 6) printf("PASS\n");
	else printf("FAIL");
	
	
	
	
}

void Test_Joses()
{
	int solgers[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int solgers_2[] = {1,2,3,4,5,6,7};
	
	if (JosesProblem(solgers, 12) == 9 &&  JosesProblem(solgers_2, 7) == 7) printf("PASS\n");
	else printf("FAIL!");
}

void Test_PrintVar()
{
	PrintVar();

}







