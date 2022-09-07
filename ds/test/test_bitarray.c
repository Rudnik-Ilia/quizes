/**********************
* Title : Worksheet 8,5 
* Author: Ilia Rudnik
* Reviewer: ira
* Date : 04/09/2022
* Status : 
***********************/

#include <stdio.h>  /* printf */
#include <limits.h> /* CHARBIT */
#include <assert.h> /* assert */
#include <string.h> /* strrev */

#include "../include/bitarray.h"

#define BYTE8_1 	0x00000000000000FF 
#define WORD 64
#define NUMBER 0xFFFFFFFFFFFFFFFF 

#define TEST(a, b) ((a) != (b)) ? printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__) : puts("PASS");



/*
static int lookup[] = {
		#include "../include/LUTtableMir.txt"
};
*/





int main()
{
	char arr[WORD + 1];
	TEST(BitArrayCountOn(NUMBER), 64);
	TEST(BitArrayCountOff(0xFFFFFFFFFFFFFBFF), 1);
	TEST(BitArraySetOff(NUMBER, 10), 0xFFFFFFFFFFFFFBFF);
	TEST(BitArraySetOn(0xFFFFFFFFFFFFFBFF, 10), NUMBER);
	TEST(BitArraySetAllOff(NUMBER),0);
	TEST(BitArraySetAllOn(0),-1lu);
	TEST(BitArrayFlipBit(0xFFFFFFFFFFFFFBFF, 10), NUMBER);
	TEST(BitArrayFlipBit(NUMBER, 10), 0xFFFFFFFFFFFFFBFF);
	TEST(BitArrayMirrorBits(0xFFFFFFFF00000000), 0x00000000FFFFFFFF);
	TEST(BitArrayRotateRight(0x56158561585617C, 4), 0xC056158561585617);
	TEST(BitArrayRotateLeft(0x56158561585617C, 4), 0x56158561585617C0);
	TEST(BitArrayGetBit(1lu, 0), 1);
	TEST(BitArrayGetBit(0, 0), 0); 
	TEST(BitArraySetBit(0, 2, 1), 4);
	TEST(BitArrayMirrorBitsLUT(0xFFFFFFFF00000000), 0x00000000FFFFFFFF);
	BitArrayToString(0x56158561585617C, arr); 
	reverse_string(arr);
	TEST(strcmp(arr, "10101100001010110000101011000010101100001010110000101111100"), 0);
	TEST(BitArrayCountOnLUT(0xFFFFFFFBFFFFFBFF), 62);
	
	
	
return 0;
}
