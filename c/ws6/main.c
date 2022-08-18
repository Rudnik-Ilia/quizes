
/**********************
* Title : Worksheet 6
* Author: Ilia Rudnik
* Reviewer: 
* Date : 20/08/2022
***********************/


#include<stdio.h> /* printf*/
#include <math.h> /* pow*/



#include"ws6.h"

void test_for_Pow2()
{
	printf("Test Pow2\n");
	if(Pow2(2,3) == 16)
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
}

void test_for_IsPowOf2_Loop()
{
	printf("Test IsPowOf2_Loop\n");
	if(IsPowOf2_Loop(8) == 1 && IsPowOf2_Loop(7) == 0)
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}

} 
void test_for_AddsOne()
{
	printf("Test AddsOne\n");
	if(AddsOne(5) == 6)
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
}
void test_For_PrintOnly3BitsOn()
{	
	unsigned int arr[] = {11,2,7,14,5,11};
	printf("Test PrintOnly3BitsOn\n");
	PrintOnly3BitsOn(arr, 6);

}

int main()
{
	test_for_Pow2();
	test_for_IsPowOf2_Loop();
	test_for_AddsOne();
	
	test_For_PrintOnly3BitsOn();
	
	
	
	











return 0;
}

