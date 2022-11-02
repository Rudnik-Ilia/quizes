


#include <stdio.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "../include/stack.h"
#include "calc.h"

#define SHIFTASCII 32

double RESULT = 0;

int STATUS = 0;

static int ACT_LUT[][64] =
    {
     /* 0 1 2 3 4 5 6 7 8 9 101112                                  =    */    
	{4,0,0,0,0,0,0,0,1,5,1,1,0,1,0,1, 7,7,7,7,7,7,7,7,7,7,7,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 /* ( */{4,0,0,0,0,0,0,0,1,3,1,1,0,1,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
 /* ) */{4,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
 /* * */{4,0,0,0,0,0,0,0,1,2,2,2,0,2,0,2, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
 /* + */{4,0,0,0,0,0,0,0,1,2,1,2,0,2,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 /* - */{4,0,0,0,0,0,0,0,1,2,1,2,0,2,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 /* / */{4,0,0,0,0,0,0,0,1,2,2,2,0,2,0,2, 13,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,13, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,10,8,0,9,0,11, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0},
	{4,0,0,0,0,0,0,0,0,0,10,8,0,9,0,11, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0},
	{4,0,0,0,0,0,0,0,0,0,10,8,0,9,0,11, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0},
	{4,0,0,0,0,0,0,0,0,0,10,8,0,9,0,11, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0},
	{4,0,0,0,0,0,0,0,0,0,10,8,0,9,0,11, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		
};

int Nothing(stack_t * stack_number, stack_t * stack_operator,char *ptr);
int PushOperatorToStack(stack_t * stack_number, stack_t * stack_operator,char *ptr);
int PushOperatorToNumberStack(stack_t *stack_number, stack_t *stack_operator, char *ptr);
int KillOperator(stack_t * stack_number, stack_t * stack_operator, char *ptr);
int Stub(stack_t * stack_number, stack_t * stack_operator, char *ptr);
int StopErrorStart(stack_t *stack_number, stack_t *stack_operator, char *ptr);
int PushNumers(stack_t *stack_number, stack_t *stack_operator, char *ptr);
int WrongSymbol(stack_t *stack_number, stack_t *stack_operator, char *ptr);

int Addition(stack_t *stack_number, stack_t *stack_operator, char *ptr);
int Subtraction(stack_t *stack_number, stack_t *stack_operator, char *ptr);
int Multiplication(stack_t *stack_number, stack_t *stack_operator, char *ptr);
int Division(stack_t *stack_number, stack_t *stack_operator, char *ptr);

int Power(stack_t *stack_number, stack_t *stack_operator, char *ptr);
static double PowerCalculate(double num1, double num2); 
size_t Reminder(int n);
int DivByZero(stack_t *stack_number, stack_t *stack_operator, char *ptr);
 
static func ARR[] = {	
			Nothing, 
			PushOperatorToStack, 
			PushOperatorToNumberStack, 
			KillOperator, 
			Stub, 
			StopErrorStart,  
			WrongSymbol, 
			PushNumers, 
			Addition, 
			Subtraction, 
			Multiplication,
			Division,
			Power,
			DivByZero
			};

int InfixToPost(char *str, double *out, size_t size)
{
	stack_t *numbers = NULL;
	stack_t *operators = NULL;
	int step = 0;
	char start_sym = ' ';
	int ch = 0;
	char x = 0;
	(void)out;

	numbers =  StackCreate(sizeof(double), size);
	operators = StackCreate(sizeof(char), size);
	
	StackPush(operators, &start_sym);
	
	while(*(str+step) && STATUS == 0)
	{
		x = *(char*)StackPeek(operators) - SHIFTASCII;
		ch = *(str+step);
		printf("%d - %d\n", x, ch - SHIFTASCII);
		step += ARR[ACT_LUT[(int)x][ch - SHIFTASCII]](numbers, operators, str+step);
	}
	
	printf("FINAL: %f\n", RESULT);
	/*
	PushOperatorToNumberStack(numbers, operators, str+step);
	printf("SIZE OPER: %ld\n", StackSize(operators));
	printf("LAST OPER: %c\n", *(char*)StackPeek(operators));
	StackPop(operators);
	printf("LAST OPER: %c\n", *(char*)StackPeek(numbers));
	StackPop(operators);
	printf("LAST OPER: %c\n", *(char*)StackPeek(numbers));
	StackPop(operators);
	printf("LAST OPER: %c\n", *(char*)StackPeek(numbers));
	StackPop(operators);
	printf("LAST OPER: %c\n", *(char*)StackPeek(numbers));
	StackPop(operators);
	printf("LAST OPER: %c\n", *(char*)StackPeek(numbers));
	printf("---------------------------------------------------------------------------");
	printf("SIZE NUM: %ld\n", StackSize(numbers));
	printf("LAST NUM: %f\n", *(double*)StackPeek(numbers));
	StackPop(numbers);
	printf("LAST NUM: %f\n", *(double*)StackPeek(numbers));
	StackPop(numbers);
	printf("LAST NUM: %f\n", *(double*)StackPeek(numbers));
	StackPop(numbers);
	printf("LAST NUM: %f\n", *(double*)StackPeek(numbers));
	StackPop(numbers);

	StackDestroy(numbers);
	StackDestroy(operators);
	*/
	return 0;
}

    
int Nothing(stack_t * stack_number, stack_t * stack_operator,char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;
	printf("im nothing\n");
	return 1;
}    

int PushOperatorToStack(stack_t * stack_number, stack_t * stack_operator,char *ptr)
{
	void *dat = NULL;
	(void)stack_number;

	dat = ptr;

	StackPush(stack_operator, dat);

	printf("PushOperatorToStack\n");
	return 1;
}

int PushOperatorToNumberStack(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	
	int index = *(char*)(StackPeek(stack_operator));

	printf("INDEX_1: %d INDEX_2: %d\n",(int)((StackSize(stack_number)+48) - 32), index - SHIFTASCII);
	
	ARR[ACT_LUT[(int)((StackSize(stack_number)+48) - 32)][index - SHIFTASCII]](stack_number, stack_operator, ptr);
	
	StackPop(stack_operator);

	printf("Push from stack operator to stack of number \n");

	return 0;
}

int KillOperator(stack_t * stack_number, stack_t * stack_operator, char *ptr)
{
	(void)stack_number;
	(void)ptr;
	StackPop(stack_operator);
	printf("KillOperator\n");

	return 1;
}

int Stub(stack_t * stack_number, stack_t * stack_operator, char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;

	printf("Stub\n");
	return 1;
}

int StopErrorStart(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;
	printf("Stop error start syntax\n");
	STATUS = 1;
	return 0;
}

int PushNumers(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	char *empty = NULL;
	double res = strtod(ptr, &empty);
	
	(void)stack_operator;
	
	StackPush(stack_number, &res);

	printf("Size Stack: %ld\n", StackSize(stack_number));
	
	return res ? Reminder(res) : 1;
}

int WrongSymbol(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;

	printf("Wrong symbol\n");
	return 1;
}

int Addition(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	double a = 0; 
	double res = 0;
	(void)stack_operator;
	(void)ptr;
	
	a = *(double*)StackPeek(stack_number);
	
	StackPop(stack_number);
	res = a + *(double*)StackPeek(stack_number);
	StackPop(stack_number);
	printf("RESULT: %f\n", res);
	
	StackPush(stack_number, &res);
	
	printf("PEEK AND SIZE: %f - %ld\n", *(double*)StackPeek(stack_number), StackSize(stack_number));
	RESULT = res;
	return 0;
}

int Subtraction(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	 double a = 0;  
	 double res = 0; 
	 (void)stack_operator; 
	 (void)ptr; 

	 a = *(double*)StackPeek(stack_number);
	 StackPop(stack_number);
	 res = *(double*)StackPeek(stack_number) - a;
	 StackPop(stack_number);
	 StackPush(stack_number, &res); 
	 printf("RESULT: %f\n", *(double*)StackPeek(stack_number)); 
	 RESULT = res;
	 return 0;
}

   
int Multiplication(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	double a = 0; 
	double res = 0;
	(void)stack_operator;
	(void)ptr;
	
	a = *(double*)StackPeek(stack_number);
	
	StackPop(stack_number);
	
	res = a * *(double*)StackPeek(stack_number);
	
	StackPop(stack_number);
	
	printf("RESULT: %f\n", res);
	
	StackPush(stack_number, &res);
	
	printf("PEEK AND SIZE: %f - %ld\n", *(double*)StackPeek(stack_number), StackSize(stack_number));
	RESULT = res;
	return 0;
}

int Division(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	
	double a = 0;  
	double res = 0; 
	(void)stack_operator; 
	(void)ptr; 
	a = *(double*)StackPeek(stack_number);
	/*
	printf("ZERO %d - %d\n", (int)((a+48)-32), *(char*)StackPeek(stack_operator)-SHIFTASCII);
	ARR[ACT_LUT[(int)((a+48)-32)][*(char*)StackPeek(stack_operator)-SHIFTASCII]](stack_number, stack_operator, ptr);
	*/
	StackPop(stack_number);
	
	res = (*(double*)StackPeek(stack_number))/a;
	
	
	
	StackPop(stack_number);

	StackPush(stack_number, &res); 
	printf("RESULT: %f\n", *(double*)StackPeek(stack_number)); 
	
	RESULT = res;
	
	return 0;
} 

int Power(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	double a = 0;  
	double b = 0;  
	double res = 0; 
	(void)stack_operator; 
	(void)ptr; 


	a = *(double*)StackPeek(stack_number);
	StackPop(stack_number);

	b = *(double*)StackPeek(stack_number);
	StackPop(stack_number);

	res = PowerCalculate(b, a);

	StackPush(stack_number, &res); 
	printf("RESULT: %f\n", *(double*)StackPeek(stack_number)); 
	RESULT = res;
	return 0;
}

int DivByZero(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	(void)stack_operator; 
	(void)ptr; 
	(void)stack_number; 
	STATUS = 1;
	printf("DIVISION BY ZERO! BYYYY\n");
	
	return 0;
}


static double PowerCalculate(double num1, double num2)
{
	double res = 1;
	double i;

	for (i = 0; i < num2; ++i)
	{
		res = res * num1;
	}

	return res;
}

size_t Reminder(int n)
{
    size_t i = 0;
    for (; n ; n /= 10)
    {
        ++i;
    }    
    return i;
} 
    
    
    
    
    

