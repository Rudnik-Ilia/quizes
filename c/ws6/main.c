
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
	printf("----------------------------\n");
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
	printf("----------------------------\n");
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
	printf("----------------------------\n");
}
void test_For_PrintOnly3BitsOn()
{	
	unsigned int arr[] = {11,2,7,14,5,11};
	printf("Test PrintOnly3BitsOn\n");
	PrintOnly3BitsOn(arr, 6);
	printf("----------------------------\n");
}

void test_for_ByteMirror_Loop()
{	
	printf("Test ByteMirror_Loop\n");
	if(ByteMirror_Loop(78) == 114 && ByteMirror_Loop(34) == 68)
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
	printf("----------------------------\n");
}

void test_for_Is2And6_On()
{
	printf("Test Is2And6_On\n");
	
	if(Is2And6_On(94) && Is2And6_On(68))
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
	printf("----------------------------\n");
}

void test_for_It2or6_On()
{
	printf("Test It2or6_On\n");
	if(It2or6_On(32) || It2or6_On(36))
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
	printf("----------------------------\n");
}

void test_for_Swap3and5()
{	
	printf("Test Swap3and5\n");
	if(Swap3and5(251) || Swap3and5(239))
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
	printf("----------------------------\n");
}

void test_for_ClosestDivBy16()
{
	printf("Test ClosestDivBy16\n");
	if(ClosestDivBy16(18) == 16 && ClosestDivBy16(37) == 32 && ClosestDivBy16(67)==64)
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
	printf("----------------------------\n");
}

void test_for_Swap2NoTemp()
{
	int x;
	int y;
	int a;
	int b;
	a = -2147483648;
	b = 500;
	x = -2147483648;
	y = 500;
	printf("Test Swap2NoTemp\n");
	Swap2NoTemp(&x, &y);
	if(a == y && b == x)
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
	printf("----------------------------\n");
	
}


void test_for_CountSetBits_Loop()
{
	printf("Test CountSetBits_Loop\n");
	
	if(CountSetBits_Loop(4567) == 8 && CountSetBits_Loop(63890) == 9)
	{
		printf("PASS\n");
	}else{
	 	printf("FAIL\n");
	}
	printf("----------------------------\n");

}


int main()
{
	test_for_Pow2();
	test_for_IsPowOf2_Loop();
	test_for_AddsOne();
	test_For_PrintOnly3BitsOn();
	test_for_ByteMirror_Loop();
	test_for_Is2And6_On();
	test_for_It2or6_On();
	test_for_Swap3and5();
	test_for_ClosestDivBy16();
	test_for_Swap2NoTemp();
	test_for_CountSetBits_Loop();
	
	
	
	











return 0;
}

