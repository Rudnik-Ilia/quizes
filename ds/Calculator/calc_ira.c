/************************************************************/
/*Title: calc.c                                             
**Author: Ira                                              
** Date: 2022-11-02                                         
** Reviewer: Ilia                                         
** Review status:                                            
************************************************************/

#include <stdlib.h> /* malloc, abs */
#include <ctype.h>  /* isdigit */
#include <string.h> /* strlen */
#include <math.h>   /* pow */
#include <float.h>  /* DBL_MAX, DBL_MIN */
#include <assert.h> /* assert */

#ifndef NDEBUG
#include <stdio.h>
#define PERROR(message) (perror(message))
#endif

#include "stack.h"
#include "calc.h"

typedef status_t (*handleFSM)(void *ptr_1, void *ptr_2, void *ptr_3, void **pptr);
typedef status_t (*MathAction)(double *a, double *b);

enum precedence
{
    RP,
    POWER,
    DIVISION,
    MULTIPLICATION, 
    MINUS,
    PLUS,
    LP
};

enum alphabet
{
/* 1 */   S_DIG = 1,
/* 2 */   S_PLS,
/* 3 */   S_MIN,
/* 4 */   S_MUL,
/* 5 */   S_DIV,
/* 6 */   S_POW,
/* 7 */   S_LP,
/* 8 */   S_RP,
/* 9 */   S_NULL,
/* 10 */  S_WHS,
/* 11 */  ALPHABET_SIZE
};

typedef enum state
{
/* 0 */     START,
/* 1 */     LOPRN,
/* 2 */     ROPRN,
/* 3 */     EOLOPRN,
/* 4 */     EOROPRN,
/* 5 */     DIV,
/* 6 */     MUL,
/* 7 */     POW,
/* 8 */     MIN,
/* 9 */     PLS,
/* 10 */    ACCEPT,
/* 11 */    RPR, 
/* 12 */    RUM, 
/* 13 */    LUM,
/* 14 */    ERROR,
/* 15 */    NUM_OF_STATES
} state_t;

#define UNUSED(member) ((void)(member))

#define SIZE_LIMIT 40
#define SIZE_OF_OPERANDS 8
#define SIZE_OF_OPERATORS 1

#define NUM_OF_FUNC_UNDER_STATE 2
#define NUM_OF_MATH_OPERATIONS 5

#define IS_DIG(sym)        ((isdigit(sym) != 0) *  S_DIG)
#define IS_PLUS(sym)       ((43 == (sym)) * S_PLS)
#define IS_MIN(sym)        ((45 == (sym)) * S_MIN)
#define IS_MUL(sym)        ((42 == (sym)) * S_MUL)
#define IS_DIV(sym)        ((47 == (sym)) * S_DIV)
#define IS_POW(sym)        ((94 == (sym)) * S_POW)
#define IS_LP(sym)         ((40 == (sym)) * S_LP)
#define IS_RP(sym)         ((41 == (sym)) * S_RP)
#define IS_TERM_NULL(sym)  (('\0' == (sym)) * S_NULL)
#define IS_WHITESPACE(sym) ((32 == (sym)) * S_WHS)

#define GET_KEY_BY_SYM(sym) (IS_DIG(sym) + IS_PLUS(sym) + IS_MIN(sym) + \
                             IS_MUL(sym) + IS_DIV(sym) + IS_POW(sym) + \
                             IS_LP(sym) + IS_RP(sym) + \
                             IS_TERM_NULL(sym) + IS_WHITESPACE(sym))

#define GET_KEY_OF_FUNC(value) (!!((ALPHABET_SIZE - 1) - value))

#define GET_PRECEDENCE(sym) (((GET_KEY_BY_SYM(sym) == S_MIN) * MINUS + \
                             ((GET_KEY_BY_SYM(sym) == S_PLS) * PLUS) + \
                             ((GET_KEY_BY_SYM(sym) == S_DIV) * DIVISION) + \
                             ((GET_KEY_BY_SYM(sym) == S_MUL) * MULTIPLICATION) + \
                             ((GET_KEY_BY_SYM(sym) == S_POW) * POWER) + \
                             ((GET_KEY_BY_SYM(sym) == S_LP) * LP) + \
                             ((GET_KEY_BY_SYM(sym) == S_RP) * RP)))

#define SIGN(num) ((int)(num > 0) - (int)(num < 0))
#define ABS(num)  ((SIGN(num) * num))

#define IS_DIV_BY_ZERO(operand) (((int)0 == ((int)operand)) * ILLEGAL_OPERATION)

#define IS_DBL_OVERFLOW_PLS(a, b) (((SIGN(a) * SIGN(b) == 1) && \
                                    (ABS(a) > DBL_MAX - ABS(b))) * DOUBLE_OVERFLOW)

#define IS_DBL_OVERFLOW_MIN(a, b) (((SIGN(a) * SIGN(b) == -1) && \
                                    (ABS(a) > DBL_MAX - ABS(b))) * DOUBLE_OVERFLOW)

#define IS_DBL_OVERFLOW_MUL(a, b) (((SIGN(a) * SIGN(b) != 0) && \
                                    ((log(ABS(a)) + log(ABS(b))) > log(DBL_MAX))) * DOUBLE_OVERFLOW)

#define IS_DBL_UNDERFLOW_MUL(a, b) (((SIGN(a) * SIGN(b) != 0) && \
                                    ((log(ABS(a)) + log(ABS(b))) < -log(DBL_MAX))) * DOUBLE_UNDERFLOW)

#define IS_DBL_OVERFLOW_DIV(a, b) (((SIGN(a) * SIGN(b) != 0) && \
                               ((log(ABS(a)) - log(ABS(b))) > log(DBL_MAX))) * DOUBLE_OVERFLOW)

#define IS_DBL_UNDERFLOW_DIV(a, b) (((SIGN(a) * SIGN(b) != 0) && \
                                ((log(ABS(a)) - log(ABS(b))) < -log(DBL_MAX))) * DOUBLE_UNDERFLOW)

static int COUNTER_OF_PARANTHESIS = 0;

static status_t FSM(const char *exp, double *out);
static stack_t *CreateStack(size_t size_of_element, size_t n_el);

static status_t Add(double *a, double *b);
static status_t Sub(double *a, double *b);
static status_t Div(double *a, double *b);
static status_t Mul(double *a, double *b);
static status_t Pow(double *a, double *b);

static status_t PushNumOnToStack(void *operands, void *operators, void *stub_1, void **stub_2);
static status_t PushOprOnToStack(void *operands, void *operators, void *stub_1, void **stub_2);
static status_t MovePointer(void *operands, void *operators, void *stub_1, void **input);

static status_t HandlePlus(void *operands, void *operators, void *stub_1, void **stub_2);
static status_t HandleMin(void *operands, void *operators, void *stub_1, void **stub_2);
static status_t HandleMul(void *operands, void *operators, void *stub_1, void **stub_2);
static status_t HandleDiv(void *operands, void *operators, void *stub_1, void **stub_2);
static status_t HandlePow(void *operands, void *operators, void *stub_1, void **stub_2);

static status_t HandleUM(void *operands, void *operators, void *stub_1, void **stub_2);

static status_t HandleLP(void *operands, void *operators, void *stub_1, void **stub_2);
static status_t HandleRP(void *operands, void *operators, void *stub_1, void **stub_2);

static status_t HandleAccept(void *operands, void *operators, void *stub_1, void **stub_2);
static status_t HandleError(void *operands, void *operators, void *stub_1, void **stub_2);

static status_t ComputationOntoStacks(stack_t *operands, stack_t *operators, int precedence, double *out);

static MathAction LUT_MATH_ACTION[NUM_OF_MATH_OPERATIONS] = {
    Add, Sub, Mul, Div, Pow
};

static handleFSM LUT_FUNC[NUM_OF_STATES][NUM_OF_FUNC_UNDER_STATE] = {
                /*   0 MovePointer        1 Action */
/* 0     START    */  {MovePointer,         HandleLP},
/* 1     LOPRN    */  {MovePointer,         PushNumOnToStack},
/* 2     ROPRN    */  {MovePointer,         PushNumOnToStack},
/* 3     EOLOPRN  */  {MovePointer,         NULL},
/* 4     EOROPRN  */  {MovePointer,         NULL},
/* 5     DIV      */  {MovePointer,         HandleDiv},
/* 6     MUL      */  {MovePointer,         HandleMul},
/* 7     POW      */  {MovePointer,         HandlePow},
/* 8     MIN      */  {MovePointer,         HandleMin},
/* 9     PLS      */  {MovePointer,         HandlePlus},
/* 10    ACCEPT   */  {MovePointer,         HandleAccept},
/* 11    RPR      */  {MovePointer,         HandleRP},
/* 12    RUM      */  {MovePointer,         HandleUM},
/* 13    LUM      */  {MovePointer,         HandleUM},
/* 14    ERROR    */  {HandleError,         HandleError}
};

static int LUT_TRANSITION_TABLE[NUM_OF_STATES][ALPHABET_SIZE] = {
                    /*      0           1          2           3              4            5             6           7            8             9              10*/
                    /*      INVALID     DIGIT      PLS         MIN            MUL          DIV           POW         LR           RP            TERM_NUL       WS */
/* 0     START    */        {ERROR,     LOPRN,     ERROR,      LUM,           ERROR,       ERROR,        ERROR,      START,       ERROR,        ERROR,         START},
/* 1     LOPRN    */        {ERROR,     LOPRN,     PLS,        MIN,           MUL,         DIV,          POW,        ERROR,       RPR,          ERROR,         EOLOPRN},
/* 2     ROPRN    */        {ERROR,     ROPRN,     PLS,        MIN,           MUL,         DIV,          POW,        ERROR,       RPR,          ACCEPT,        EOROPRN},
/* 3     EOLOPRN  */        {ERROR,     ERROR,     PLS,        MIN,           MUL,         DIV,          POW,        ERROR,       RPR,          ERROR,         EOLOPRN},
/* 4     EOROPRN  */        {ERROR,     ERROR,     PLS,        MIN,           MUL,         DIV,          POW,        ERROR,       RPR,          ACCEPT,        EOROPRN},
/* 5     DIV      */        {ERROR,     ROPRN,     ERROR,      ERROR,         ERROR,       ERROR,        ERROR,      START,       ERROR,        ERROR,         DIV},
/* 6     MUL      */        {ERROR,     ROPRN,     ERROR,      ERROR,         ERROR,       ERROR,        ERROR,      START,       ERROR,        ERROR,         MUL},
/* 7     POW      */        {ERROR,     ROPRN,     ERROR,      RUM,           ERROR,       ERROR,        ERROR,      START,       ERROR,        ERROR,         POW},
/* 8     MIN      */        {ERROR,     ROPRN,     ERROR,      RUM,           ERROR,       ERROR,        ERROR,      START,       ERROR,        ERROR,         MIN},
/* 9     PLS      */        {ERROR,     ROPRN,     ERROR,      RUM,           ERROR,       ERROR,        ERROR,      START,       ERROR,        ERROR,         PLS},
/* 10    ACCEPT   */        {ACCEPT,    ACCEPT,    ACCEPT,     ACCEPT,        ACCEPT,      ACCEPT,       ACCEPT,     ACCEPT,      ACCEPT,       ACCEPT,        ACCEPT},
/* 11    RPR      */        {ERROR,     ERROR,     PLS,        MIN,           MUL,         DIV,          POW,        ERROR,       RPR,          ACCEPT,        RPR},
/* 12    RUM      */        {ERROR,     ROPRN,     ERROR,      ERROR,         ERROR,       ERROR,        ERROR,      START,       ERROR,        ERROR,         RUM},
/* 13    LUM      */        {ERROR,     LOPRN,     ERROR,      ERROR,         ERROR,       ERROR,        ERROR,      START,       ERROR,        ERROR,         LUM},
/* 14    ERROR    */        {ERROR,     ERROR,     ERROR,      ERROR,         ERROR,       ERROR,        ERROR,      ERROR,       ERROR,        ERROR,         ERROR}
};                  

static status_t FSM(const char *exp, double *out)
{
    status_t status = SUCCESS;
    state_t curr_state = START;

    stack_t *operands = NULL;
    stack_t *operators = NULL;

    int key_of_sym = 0;

    char *input = NULL;
    char **ptr = NULL;

    operands = CreateStack(SIZE_OF_OPERANDS, SIZE_LIMIT);
    if (NULL == operands)
    {
        status = MALLOC_ERR;
        PERROR("Memory was not allocated!");
        return status;
    }
    operators = CreateStack(SIZE_OF_OPERATORS, SIZE_LIMIT);
    if (NULL == operators)
    {
        status = MALLOC_ERR;
        PERROR("Memory was not allocated!");
        free(operands);
        return status;
    }

    input = (char *)exp;
    ptr = &input;

    COUNTER_OF_PARANTHESIS = 0;

    while (ACCEPT != curr_state && ERROR != curr_state && !status)
    {
        key_of_sym = GET_KEY_BY_SYM(*input);
        curr_state = LUT_TRANSITION_TABLE[curr_state][key_of_sym];
        status = LUT_FUNC[(size_t)curr_state][GET_KEY_OF_FUNC(key_of_sym)](operands, operators, out, (void **)ptr);
    }

    free(operands);
    free(operators);
    return status;
}

status_t Calculate(const char *exp, double *out)
{
    status_t status = FSM(exp, out);
    return status;
}

static status_t HandleAccept(void *operands, void *operators, void *out, void **stub_1)
{
    status_t status = SUCCESS;
    double a = 0;
    double b = 0;
    char opr = '\0';

    UNUSED(stub_1);

    while (COUNTER_OF_PARANTHESIS)
    {
        return SYNTAX_ERR;
    }

    while (!StackIsEmpty((stack_t *)operators) && !status)
    {
        opr = *(char *)StackPeek((stack_t *)operators);

        a = *(double *)StackPeek((stack_t *)operands);
        StackPop((stack_t *)operands);
    
        b = *(double *)(StackPeek((stack_t *)operands));
        StackPop((stack_t *)operands);

        status = LUT_MATH_ACTION[GET_KEY_BY_SYM(opr) - 2](&b, &a);
        *(double *)out = b;

        StackPush((stack_t *)operands, out);
        StackPop((stack_t *)operators);
    }

    *(double *)out = *(double *)StackPeek((stack_t *)operands);
    StackPop((stack_t *)operands);
    return status;
}

static status_t HandlePlus(void *operands, void *operators, void *out, void **input)
{
    status_t status = SUCCESS;
    char sym = *(char *)*input;

    status = ComputationOntoStacks((stack_t *)operands, (stack_t *)operators, GET_PRECEDENCE(sym), (double *)out);

    MovePointer(NULL, NULL, NULL, input);
    PushOprOnToStack(NULL, operators, &sym, NULL);
    return status;
}

static status_t HandleMin(void *operands, void *operators, void *out, void **input)
{
    status_t status = SUCCESS;
    char sym = *(char *)*input;

    status = ComputationOntoStacks((stack_t *)operands, (stack_t *)operators, GET_PRECEDENCE(sym), (double *)out);

    MovePointer(NULL, NULL, NULL, input);
    PushOprOnToStack(NULL, operators, &sym, NULL);
    return status;
}

static status_t HandleMul(void *operands, void *operators, void *out, void **input)
{
    status_t status = SUCCESS;
    char sym = *(char *)*input;

    status = ComputationOntoStacks((stack_t *)operands, (stack_t *)operators, GET_PRECEDENCE(sym), (double *)out);

    MovePointer(NULL, NULL, NULL, input);
    PushOprOnToStack(NULL, operators, &sym, NULL);
    return status;
}

static status_t HandleDiv(void *operands, void *operators, void *out, void **input)
{
    status_t status = SUCCESS;
    char sym = *(char *)*input;

    status = ComputationOntoStacks((stack_t *)operands, (stack_t *)operators, GET_PRECEDENCE(sym), (double *)out);

    MovePointer(NULL, NULL, NULL, input);
    PushOprOnToStack(NULL, operators, &sym, NULL);
    return status;
}

static status_t HandlePow(void *operands, void *operators, void *out, void **input)
{
    status_t status = SUCCESS;
    char sym = *(char *)*input;

    status = ComputationOntoStacks((stack_t *)operands, (stack_t *)operators, GET_PRECEDENCE(sym), (double *)out);

    MovePointer(NULL, NULL, NULL, input);
    PushOprOnToStack(NULL, operators, &sym, NULL);
    return status;
}

static status_t HandleUM(void *operands, void *operators, void *stub_1, void **input)
{
    status_t status = SUCCESS;
    char sym = '*';
    double minus = -1.0;
    UNUSED(stub_1);
    status = MovePointer(NULL, NULL, NULL, input);
    StackPush((stack_t *)operands, &minus);
    PushOprOnToStack(NULL, operators, &sym, NULL);
    return status;
}

static status_t HandleLP(void *operands, void *operators, void *stub_1, void **input)
{
    status_t status = SUCCESS;
    char sym = *(char *)*input;
    UNUSED(operands);
    UNUSED(stub_1);
    status = MovePointer(NULL, NULL, NULL, input);
    PushOprOnToStack(NULL, operators, &sym, NULL);
    ++COUNTER_OF_PARANTHESIS;
    return status;
}

static status_t HandleRP(void *operands, void *operators, void *out, void **input)
{
    status_t status = SUCCESS;
    char operator = '\0';
    double a = 0.0;
    double b = 0.0;

    operator = *(char *)StackPeek((stack_t *)operators);
    StackPop((stack_t *)operators);
    while (!StackIsEmpty((stack_t *)operators) && S_LP != GET_KEY_BY_SYM(operator) && !status)
    {
        a = *(double *)StackPeek((stack_t *)operands);
        StackPop((stack_t *)operands);

        b = *(double *)StackPeek((stack_t *)operands);
        StackPop((stack_t *)operands);

        status = LUT_MATH_ACTION[GET_KEY_BY_SYM(operator) - 2](&b, &a);

        *(double *)out = b;
        StackPush((stack_t *)operands, out);

        operator = *(char *)StackPeek((stack_t *)operators);
        StackPop((stack_t *)operators);
    }
    --COUNTER_OF_PARANTHESIS;
    status = MovePointer(NULL, NULL, NULL, input);
    return status;
}

static status_t HandleError(void *operands, void *operators, void *stub_1, void **stub_2)
{
    status_t status = SYNTAX_ERR;
    UNUSED(operands);
    UNUSED(operators);
    UNUSED(stub_1);
    UNUSED(stub_2);
    return status;
}

static status_t MovePointer(void *operands, void *operators, void *stub_3, void **input)
{
    status_t status = SUCCESS;
    char *ptr = *input;
    UNUSED(operands);
    UNUSED(operators);
    UNUSED(stub_3);
    ++ptr;
    *input = ptr;
    return status;
}

static status_t PushNumOnToStack(void *operands, void *operators, void *stub_1, void **input)
{
    status_t status = SUCCESS;
    char *ptr = *input;
    double num = 0.0;

    UNUSED(operators);
    UNUSED(stub_1);

    num = strtod(*((char **)input), &ptr);
    *input = ptr;

    StackPush(((stack_t *)operands), &num);
    return status;
}

static status_t PushOprOnToStack(void *operands, void *operators, void *sym, void **stub_1)
{
    status_t status = SUCCESS;
    UNUSED(operands);
    UNUSED(stub_1);
    StackPush((stack_t *)operators, sym);
    return status;
}

static status_t Add(double *a, double *b)
{
    status_t status = IS_DBL_OVERFLOW_PLS(*a, *b);
    while (status)
    {
        return status;
    }
    (*(double *)a) += *(double *)b;
    return status;
}

static status_t Sub(double *a, double *b)
{
    status_t status = IS_DBL_OVERFLOW_MIN(*a, *b);
    while (status)
    {
        return status;
    }
    (*(double *)a) -= *(double *)b;
    return status;
}

static status_t Div(double *a, double *b)
{
    status_t status = IS_DIV_BY_ZERO(*(double *)b) + IS_DBL_UNDERFLOW_DIV(*a, *b) + IS_DBL_OVERFLOW_DIV(*a, *b);
    while (status)
    {
        return status;
    }
    (*(double *)a) /= *(double *)b;
    return status;
}

static status_t Mul(double *a, double *b)
{
    status_t status = IS_DBL_OVERFLOW_MUL(*a, *b) + IS_DBL_UNDERFLOW_MUL(*a, *b);
    while (status)          
    {
        return status;
    }
    (*(double *)a) *= *(double *)b;
    return status;
}

static status_t Pow(double *a, double *b)
{
    status_t status = SUCCESS;
    (*(double *)a) = pow(*(double *)a, *(double *)b);
    return status;
}

static status_t ComputationOntoStacks(stack_t *operands, stack_t *operators, int precedence, double *out)
{
    status_t status = SUCCESS;

    char operator = '\0';
    double a = 0.0;
    double b = 0.0;

    while (!StackIsEmpty(operators) && (precedence > GET_PRECEDENCE(*(char *)StackPeek(operators))) && !status)
    {
        operator = *(char *)StackPeek((stack_t *)operators);
        StackPop((stack_t *)operators);

        a = *(double *)StackPeek((stack_t *)operands);
        StackPop((stack_t *)operands);

        b = *(double *)StackPeek((stack_t *)operands);
        StackPop((stack_t *)operands);

        status = LUT_MATH_ACTION[GET_KEY_BY_SYM(operator) - 2](&b, &a);

        *(double *)out = b;
        StackPush((stack_t *)operands, out);
    }

    return status;
}

static stack_t *CreateStack(size_t size_of_element, size_t n_el)
{
    stack_t *stack = StackCreate(size_of_element, n_el);
    if (NULL == stack)
    {
        #ifndef NDEBUG
        PERROR("Memory was not allocated!");
        #endif
        return NULL;
    }
    return stack;
}

