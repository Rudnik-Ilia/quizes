#ifndef __CALC_H__
#define __CALC_H__

#include "../include/stack.h"


typedef int (*func)(stack_t * op_d, stack_t * op_or, char *ptr);
/*
typedef enum status status_t

typedef enum status {
	SUCCESS,
	SYNTAX_ERR,
	ILLEGAL_OPERATION,
	MALLOC_ERR,
	STACK_OVERFLOW,
	DOUBLE_OVERFLOW,
	DOUBLE_UNDERFLOW
}status_t;
*/



/*
* Description: The function calculate mathematical expression @exp and write answer to @out.
* Parameters: 
*  @exp is an mathematical expression 
*  @out result of calculation (memory pointed by @out should be allocated)
* Return: @status_t, that is 0 on success
* Complexity: 
*	 BC: O(n)
*    WC: O(n^m)
*    AVR: O(n)
*    Space: O(n)
*/
int Calculate(const char *exp, double *out);


int MainFunc(char *str, double *out, size_t size);

#endif /* __CALC_H__ */
