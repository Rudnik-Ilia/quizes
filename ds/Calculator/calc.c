


#include <stdio.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "../include/stack.h"
#include "calc.h"



static int ACT_LUT[][9] =
    {
        {4,1,5,1,1,0,1,0,1},
        {5,1,3,1,1,0,1,0,1},
        {0,0,0,0,0,0,0,0,0},
        {2,1,2,2,2,0,2,0,2},
        {2,1,2,1,2,0,2,0,1},
        {0,0,0,0,0,0,0,0,0},
        {2,1,2,1,2,0,2,0,1},
        {0,0,0,0,0,0,0,0,0},
        {2,1,2,2,2,0,2,0,2}
    };
    
void Zero(stack_t * op_d, stack_t * op_or, void *data, char *ptr)
{
	(void)op_d;
	(void)op_or;
	(void)data;
	printf("im zero\n");
}    
void First(stack_t * op_d, stack_t * op_or, void *data, char *ptr)
{
	(void)op_d;
	(void)op_or;
	(void)data;

	printf("im first\n");
}

void Second(stack_t * op_d, stack_t * op_or, void *data, char *ptr)
{
	(void)op_d;
	(void)op_or;
	(void)data;
	
	printf("im second\n");
}

void Third(stack_t * op_d, stack_t * op_or, void *data, char *ptr)
{
	(void)op_d;
	(void)op_or;
	(void)data;
	
	printf("im third\n");
}

void Four(stack_t * op_d, stack_t * op_or, void *data, char *ptr)
{
	(void)op_d;
	(void)op_or;
	(void)data;
	
	printf("im four\n");
}

void Five(stack_t * op_d, stack_t * op_or, void *data, char *ptr)
{
	(void)op_d;
	(void)op_or;
	(void)data;
	
	printf("im five\n");
}
  
static func ARR[] = {Zero, First, Second, Third, Four, Five};


int InfixToPost(char *str, double *out, size_t size)
{
	stack_t *operand = NULL;
	stack_t *operator = NULL;
	void *data = NULL;

	size_t i = 0;
	
	int ch = 0;
	int x = 0;

	operator = StackCreate(sizeof(char), size);
	operand =  StackCreate(sizeof(char), size);
	
	
	for(i = 0; i < 6; i++)
	{
		x = 4;
		ch = *(str + i);
		
		printf("%d - %d\n", x, ch - 39);
		printf("%d\n", ACT_LUT[x][ch - 39]);
		ARR[ACT_LUT[x][ch - 39]](operand, operator, data, str);
	}
	
	/*
	for(i = 0; i < size; i++)
	{	
		printf("%d - %d\n", x, (ch - 39));
		printf("%d", ACT_LUT[ch - 39][ch - 39]);
		ARR[ACT_LUT[ch - 39][ch - 39]](operand, operator, data, str);
		ch = *str++;
	}	
	*/
	
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
    
    
    
    
    
    
    
    

