


#include <stdio.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h>
#include <alloca.h> 
#include "../include/stack.h"
#include "calc.h"

#define SHIFTASCII 32


#define STATE(a, b) ((a) == (b) ? 0 : 1)

double RESULT = 0;
double FINAL_RESULT = 0;

int STATUS = 0;
int MINUS = 0;

static int ACT_LUT[][64] =
    {
     /* 0 1 2 3 4 5 6 7 8 9 101112                                  =    */    
	{4,0,0,0,0,0,0,0,1,5,1,1,0,1,0,1, 7,7,7,7,7,7,7,7,7,7,7,0,0,14,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 /* ( */{4,0,0,0,0,0,0,0,1,3,1,1,0,1,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,6,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
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
	{2,0,0,0,0,0,0,0,1,2,2,2,0,2,0,2, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
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
int Finish(stack_t *stack_number, stack_t *stack_operator, char *ptr);
char *DeleteSpace(const char *str, char *dest); 

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
			DivByZero,
			Finish
};

int Calculate(const char *exp, double *out)
{
	size_t size = strlen(exp);
	char *str = alloca(size);
	
	DeleteSpace(exp, str);

	MainFunc(str, out, size);
	*out = FINAL_RESULT;
	return MainFunc(str, out, size);
}




int MainFunc(char *str, double *out, size_t size)
{
	stack_t *numbers = NULL;
	stack_t *operators = NULL;
	int step = 0;
	char start_sym = ' ';
	int ch = 0;
	char x = 0;
	
	STATUS=0;
	
	numbers =  StackCreate(sizeof(double), size);
	operators = StackCreate(sizeof(char), size);
	
	StackPush(operators, &start_sym);
	
	while(*(str+step) && STATUS == 0)
	{
		if(*(str+step) == '-' && (*(str+step-1) == '(' || *(str+step-1) == ' '))
		{
			MINUS = 1;
			step+=1;
		}
		else 
		{
			x = *(char*)StackPeek(operators) - SHIFTASCII;
			ch = *(str+step);
			printf("%d - %d\n", x, ch - SHIFTASCII);
			step += ARR[ACT_LUT[(int)x][ch - SHIFTASCII]](numbers, operators, str+step);
		}
		FINAL_RESULT = RESULT;
	}
	
	printf("FINAL: %f\n", FINAL_RESULT);
	
	
	StackDestroy(numbers);
	StackDestroy(operators);
	
	return STATE(FINAL_RESULT, *out);
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
	(void)stack_number;

	StackPush(stack_operator, ptr);

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
	if(MINUS)
	{
		printf("We have minys!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		res *= -1;
		MINUS = 0;
	}
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
	STATUS = 1;
	return 1;
}

int Finish(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;
	printf("I am finish\n");
	return 1;
}

/********************************************************************************************************************/

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
	STATUS = 2;
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

char *DeleteSpace(const char *str, char *dest) 
{
	int i,j;
	
	for(i = j = 0; str[i] != '\0'; ++i)
	{
		if(str[i] != ' ')
		{
		    dest[j++] = str[i];
		 }
	}	    
	dest[j] = '\0';
		
	return (dest);
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

