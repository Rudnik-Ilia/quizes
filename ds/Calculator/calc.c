


#include <stdio.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "../include/stack.h"
#include "calc.h"

#define SHIFTASCII 32

static int ACT_LUT[][64] =
    {
	{4,0,0,0,0,0,0,0,1,5,1,1,0,1,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{5,0,0,0,0,0,0,0,1,3,1,1,0,1,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,1,2,2,2,0,2,0,2, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,1,2,1,2,0,2,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,1,2,1,2,0,2,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,1,2,2,2,0,2,0,2, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		
};
         
int Nothing(stack_t * stack_number, stack_t * stack_operator, void *data, char *ptr)
{
  (void)stack_number;
  (void)stack_operator;
  (void)data;
  (void)ptr;
  printf("im nothing\n");
  return 1;
}    

int PushOperatorToStack(stack_t * stack_number, stack_t * stack_operator, void *data, char *ptr)
{
  void *dat = NULL;
  (void)stack_number;
  (void)data;

  dat = ptr;
  
  StackPush(stack_operator, dat);

  printf(" push to stack\n");
  return 1;
}

int PushOperatorToNumberStack(stack_t * stack_number, stack_t * stack_operator, void *data, char *ptr)
{
  void *dat = NULL;
  (void)data;

  dat = ptr;
  
  StackPush(stack_number, StackPeek(stack_operator));
  StackPop(stack_operator);

  printf("Push from stack operator to stack of number \n");
  
  return 0;
}

int KillOperator(stack_t * stack_number, stack_t * stack_operator, void *data, char *ptr)
{
  (void)stack_number;
  (void)data;

  StackPop(stack_operator);
  printf("KillOperator(\n");
  
  return 1;
}

int Stub(stack_t * stack_number, stack_t * stack_operator, void *data, char *ptr)
{
  (void)stack_number;
  (void)stack_operator;
  (void)data;
  (void)ptr;

  printf("Stub\n");
  return 0;
}

int StopErrorStart(stack_t *stack_number, stack_t *stack_operator, void *data, char *ptr)
{
  (void)stack_number;
  (void)stack_operator;
  (void)data;
  
  printf("Stop error start syntax\n"); /* error on start, when we get wrong operand */
  return 0;
}

int PushNumers(stack_t *stack_number, stack_t *stack_operator, void *data, char *ptr)
{
  void *dat = NULL;
  (void)stack_operator;
  (void)data;
  
  dat = ptr;
  
  StackPush(stack_number, dat);
  
  printf("PushNumbers\n");
  return 1;
}

int WrongSymbol(stack_t *stack_number, stack_t *stack_operator, void *data, char *ptr)
{
  (void)stack_number;
  (void)stack_operator;
  (void)data;
  (void)ptr;  
  printf("Wrong symbol\n");
  return 1;
}
  
static func ARR[] = {Nothing, PushOperatorToStack, PushOperatorToNumberStack, KillOperator, Stub, StopErrorStart,  WrongSymbol, PushNumers};


int InfixToPost(char *str, double *out, size_t size)
{
	stack_t *numbers = NULL;
	stack_t *operators = NULL;
	void *data = NULL;
	int step = 0;
	
	char start_sym = ' ';
	
	size_t i = 0;
	
	int ch = 0;
	char x = 0;

	numbers =  StackCreate(sizeof(char), size);
	
	operators = StackCreate(sizeof(char), size);
	
	StackPush(operators, &start_sym);
	
	
	for(i = 0; i < 3; i++)
	{
		x = *(char*)StackPeek(operators) - SHIFTASCII;
		ch = *(str + step);
		
		printf("%d - %d\n", x, ch - SHIFTASCII);
		
		printf("%d\n", ACT_LUT[x][ch - SHIFTASCII]);
		
		step = ARR[ACT_LUT[x][ch - SHIFTASCII]](numbers, operators, data, str);
		
	
	}
	
	printf("LAST OPER: %c\n", *(char*)StackPeek(operators));
	printf("LAST NUM: %c\n", *(char*)StackPeek(operators));
	return 0;
}


/*
static int IsOperator(char symbol)
{
	return (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-');
	
}	

static int isOperand(char symbol)
{
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
}  
    
  */  
    
    
    
    
    
    
    
    

