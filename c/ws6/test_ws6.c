
/**********************
* Title : Worksheet 6
* Author: Ilia Rudnik
* Reviewer: 
* Date : 20/08/2022
***********************/


#include<stdio.h> /* printf*/


#include"ws6.h"

void TestForPow2();
void TestForIsPowOf2_Loop();
void TestForAddsOne();
void TestForPrintOnly3BitsOn();
void TestForByteMirror_Loop();
void TestForIs2And6_On();
void TestForIt2or6_On();
void TestForSwap3and5();
void TestForClosestDivBy16();
void TestForSwap2NoTemp();
void TestForCountSetBits_Loop();
	

int main()
{
	TestForPow2();
	TestForIsPowOf2_Loop();
	TestForAddsOne();
	TestForPrintOnly3BitsOn();
	TestForByteMirror_Loop();
	TestForIs2And6_On();
	TestForIt2or6_On();
	TestForSwap3and5();
	TestForClosestDivBy16();
	TestForSwap2NoTemp();
	TestForCountSetBits_Loop();
	
return 0;
}


void TestForPow2()
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

void TestForIsPowOf2_Loop()
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
void TestForAddsOne()
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
void TestForPrintOnly3BitsOn()
{	
	unsigned int arr[] = {11,2,7,14,5,11};
	printf("Test PrintOnly3BitsOn\n");
	PrintOnly3BitsOn(arr, 6);
	printf("----------------------------\n");
}

void TestForByteMirror_Loop()
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

void TestForIs2And6_On()
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

void TestForIt2or6_On()
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

void TestForSwap3and5()
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

void TestForClosestDivBy16()
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

void TestForSwap2NoTemp()
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


void TestForCountSetBits_Loop()
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

