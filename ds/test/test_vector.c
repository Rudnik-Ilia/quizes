
/**********************
* Title : Worksheet 8,5 
* Author: Ilia Rudnik
* Reviewer: ira
* Date : 04/09/2022
* Status : 
***********************/

#include <stdio.h>  /* printf */

#include "../include/vector.h"

#define TEST(a, b) ((a) != (b)) ? printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__) : puts("PASS");

void Test_IntVector()
{

	int i;
	int a = 888;
	int b = 777;
	int c = 555;
	int arr[] = {10, 20, 30, 40, 50};
	vector_t* IntVector = VectorCreate(4, 5);
	printf("Test for IntVector: \n");
	
	TEST(VectorIsEmpty(IntVector), 1);
	
	for(i = 0; i < 5; ++i)
	{
		VectorPushBack(IntVector, &arr[i]);
	}
	
	TEST(VectorCapacity(IntVector), 5);
	TEST(VectorSize(IntVector), 5);
	TEST(*(int*)VectorGetAccessToElement(IntVector, 0), 10);
	TEST(*(int*)VectorGetAccessToElement(IntVector, 4), 50);
	TEST(VectorSize(IntVector), 5);
	
	VectorPopBack(IntVector);

	TEST(VectorSize(IntVector), 4);
	
	VectorReserve(IntVector, 8);
	
	TEST(VectorCapacity(IntVector), 8);
	
	VectorPushBack(IntVector, &a);
	VectorPushBack(IntVector, &b);
	VectorPushBack(IntVector, &c);
	
	TEST(VectorSize(IntVector), 7);
	TEST(*(int*)VectorGetAccessToElement(IntVector, 6), 555);
	TEST(VectorIsEmpty(IntVector), 0);
	
	printf("=====================================================================\n");
	
	VectorDestroy(IntVector);	
}

void Test_CharVector()
{

	int i;
	char a = 'a';
	char b = 'b';
	char c = 'c';
	char arr[] = {'d', 'e', 'f', 'g', 'i'};
	vector_t* IntVector = VectorCreate(1, 5);
	printf("Test for CharVector: \n");
	
	TEST(VectorIsEmpty(IntVector), 1);
	
	for(i = 0; i < 5; ++i)
	{
		VectorPushBack(IntVector, &arr[i]);
	}
	
	TEST(VectorCapacity(IntVector), 5);
	TEST(VectorSize(IntVector), 5);
	TEST(*(char*)VectorGetAccessToElement(IntVector, 0), 'd');
	TEST(*(char*)VectorGetAccessToElement(IntVector, 4), 'i');
	TEST(VectorSize(IntVector), 5);
	
	VectorPopBack(IntVector);

	TEST(VectorSize(IntVector), 4);
	
	VectorReserve(IntVector, 8);
	
	TEST(VectorCapacity(IntVector), 8);
	
	VectorPushBack(IntVector, &a);
	VectorPushBack(IntVector, &b);
	VectorPushBack(IntVector, &c);
	
	TEST(VectorSize(IntVector), 7);
	TEST(*(char*)VectorGetAccessToElement(IntVector, 6), 'c');
	
	VectorSetElement(IntVector,5, &b);
	
	TEST(*(char*)VectorGetAccessToElement(IntVector, 5), 'b');
	
	TEST(VectorIsEmpty(IntVector), 0);
	
	printf("=====================================================================\n");
	
	VectorDestroy(IntVector);	
}



int main()
{
	Test_IntVector();
	Test_CharVector();
	
	

return 0;
}
