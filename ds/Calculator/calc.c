/**********************
* Title : CULCULATR!
* Author: Ilia Rudnik
* Reviewer: MARIIA
* Date : 10/11/2022
* Status : approved
***********************/

/*ONLY ONE "IF"!!!!!!!!*/

#include <stdio.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <alloca.h> /*just for experiment*/

#include "../include/stack.h"
#include "calc.h"

#define SHIFTASCII 32

int MINUS = 0;
double RESULT = 0;
double FINAL_RESULT = 0;
int STATUS = 0;

/***********************************IT'S THE MATRIX.DON'T CHANGE MATRIX!!!NEVER!!!ONLY NEO CAN CHANGE THE MATRIX******************************/

static int ACT_LUT[][64] =
    {
        /********VECTOR X IS POINTER TO INPUT******************/ 
        /********VECTOR Y IS PEEK OF STACK WITH OPERATIRS******/ 
        
	{4,0,0,0,0,0,0,0,1,5,1,1,0,1,0,1, 7,7,7,7,7,7,7,7,7,7,7,0,0,14,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,1,3,1,1,0,1,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,6,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,1,2,2,2,0,2,0,2, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,1,2,1,2,0,2,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,1,2,1,2,0,2,0,1, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{4,0,0,0,0,0,0,0,1,2,2,2,0,2,0,2, 13,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	
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
	{2,0,0,0,0,0,0,0,1,2,2,2,0,2,0,2, 7,7,7,7,7,7,7,7,7,7,7,7,7,2,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	
};

int MainFunc(char *str, double *out, size_t size);
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
void FirstMinus(stack_t *stack_number, stack_t *stack_operator);
double GetFromStack(stack_t *stack);

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
	
	assert(NULL != exp);
	assert(NULL != out);
	
	DeleteSpace(exp, str);
	MainFunc(str, out, size);
	*out = FINAL_RESULT;
	
	return STATUS;
}

int MainFunc(char *str, double *out, size_t size)
{
	stack_t *numbers = NULL;
	stack_t *operators = NULL;
	int step = 0;
	char start_sym = ' ';
	(void)out;
	
	assert(NULL != str);
	assert(NULL != out);
	
	STATUS=0;
	
	numbers =  StackCreate(sizeof(double), size);
	operators = StackCreate(sizeof(char), size);
	
	StackPush(operators, &start_sym);
	
	while(*(str+step) && STATUS == 0)
	{
		while(*(str) == '-' && (StackIsEmpty(numbers) == 1 && *(int*)StackPeek(operators) == 32))
		{
		 	FirstMinus(numbers, operators);
		 	step+=1;
		}
		while(*(str+step) == '-' && (*(str+step-1) == '('))
		{
			MINUS = 1;
			step+=1;
		}
		step += ARR[ACT_LUT[*(char*)StackPeek(operators) - SHIFTASCII][*(str+step) - SHIFTASCII]](numbers, operators, str+step);
		FINAL_RESULT = RESULT;
	}
	printf("FINAL: %f\n", FINAL_RESULT);
	StackDestroy(numbers);
	StackDestroy(operators);
	return 0;
}

/*************************************************ACTION*****************************************************/  
  
int Nothing(stack_t * stack_number, stack_t * stack_operator,char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);
	
	return 1;
}    

int PushOperatorToStack(stack_t * stack_number, stack_t * stack_operator,char *ptr)
{
	(void)stack_number;
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);

	StackPush(stack_operator, ptr);

	return 1;
}

int PushOperatorToNumberStack(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	
	int index = *(char*)(StackPeek(stack_operator));
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);
	
	ARR[ACT_LUT[(int)((StackSize(stack_number)+48) - 32)][index - SHIFTASCII]](stack_number, stack_operator, ptr);
	
	StackPop(stack_operator);

	return 0;
}

int KillOperator(stack_t * stack_number, stack_t * stack_operator, char *ptr)
{
	(void)stack_number;
	(void)ptr;
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);
	
	StackPop(stack_operator);

	return 1;
}

int Stub(stack_t * stack_number, stack_t * stack_operator, char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);

	return 1;
}

int StopErrorStart(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);
	
	STATUS = 1;
	return 1;
}

int PushNumers(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	char *empty = NULL;
	double res = strtod(ptr, &empty);
	(void)stack_operator;
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);
	
	while(MINUS)
	{
		res *= -1;
		MINUS = 0;
	}
	StackPush(stack_number, &res);
	return res ? Reminder(res) : 1;
}

int WrongSymbol(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);
	
	STATUS = 1;
	return 1;
}

int Finish(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	(void)stack_number;
	(void)stack_operator;
	(void)ptr;
	
	assert(NULL != stack_number);
	assert(NULL != stack_operator);
	assert(NULL != ptr);
	
	return 1;
}

void FirstMinus(stack_t *stack_number, stack_t *stack_operator)
{	
	double one = -1;
	char c = '*';
	
	StackPush(stack_number, &one);
	StackPush(stack_operator, &c);
}

/**********************************MATH FUNC**********************************************************************************/

int Addition(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	double a = 0; 
	double res = 0;
	(void)stack_operator;
	(void)ptr;
	
	a = GetFromStack(stack_number);
	res = a + GetFromStack(stack_number);
	StackPush(stack_number, &res);
	
	RESULT = res;
	return 0;
}

int Subtraction(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	 double a = 0;  
	 double res = 0; 
	 (void)stack_operator; 
	 (void)ptr; 

	 a = GetFromStack(stack_number);
	 res = GetFromStack(stack_number) - a;
	 StackPush(stack_number, &res); 
	
	 RESULT = res;
	 return 0;
}

   
int Multiplication(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	double a = 0; 
	double res = 0;
	(void)stack_operator;
	(void)ptr;
	
	a = GetFromStack(stack_number);
	res = a * GetFromStack(stack_number);
	StackPush(stack_number, &res);
	
	RESULT = res;
	return 0;
}

int Division(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	
	double a = 0;  
	double res = 0; 
	(void)stack_operator; 
	(void)ptr; 
	
	a = GetFromStack(stack_number);
	res = (GetFromStack(stack_number))/a;
	StackPush(stack_number, &res); 
	
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

	a = GetFromStack(stack_number);
	b = GetFromStack(stack_number);
	res = PowerCalculate(b, a);

	StackPush(stack_number, &res); 

	RESULT = res;
	return 0;
}

int DivByZero(stack_t *stack_number, stack_t *stack_operator, char *ptr)
{
	(void)stack_operator; 
	(void)ptr; 
	(void)stack_number; 
	STATUS = 2;
	FINAL_RESULT = 0;
	return 0;
}


static double PowerCalculate(double num1, double num2)
{
	double res = 1;
	double i;

	if (num2 < 0)
	{
		num2 = num2 * (-1);
		num1 = 1/num1;
	}    

	for (i = 0; i < num2; ++i)
	{
		res = res * num1;
	}
	return res;
}

/*******************HELP FUNC**********************************/
double GetFromStack(stack_t *stack)
{
	double tmp = *(double*)StackPeek(stack);
	StackPop(stack);
	return tmp;
} 

char *DeleteSpace(const char *str, char *dest) 
{
	int i = 0;
	int j = 0;
	
	for(i = j = 0; str[i] != '\0'; ++i)
	{
		if(str[i] != ' ')                            /*****MY SINGLE IF*******/
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

