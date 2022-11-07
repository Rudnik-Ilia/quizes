/*******************************************
* Filename: stack.c                        *
* Purpose: Implementation of API of stack  *
* Title: Stack                             *
* Author: Timofey Dankevich                *
* Date: 04.09.2022                         *
* Reviewer: Walter                         *
* Review status: Approved                  *
*******************************************/

#include <stdlib.h> /* malloc, free     */
#include <string.h> /* memcpy, memset   */
#include <assert.h> /* assert           */

#include "../include/stack.h" /* my own API of stack */

struct stack
{
    size_t capacity;
    size_t element_size;
    void *elements;
};

stack_t *StackCreate(size_t element_size, size_t num_of_elements)
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t) + (element_size * num_of_elements));
    if (NULL == stack)
    {
        return NULL;
    }
    stack->capacity = num_of_elements;
    stack->element_size = element_size;
    stack->elements = (void *)((char *)stack + sizeof(stack_t));
    return stack;
}

void StackDestroy(stack_t *stack)
{
    assert(NULL != stack);
    free(stack);
}

void StackPush(stack_t *stack, const void *data)
{
    assert(NULL != stack);
    assert(NULL != data);
    memcpy(stack->elements, data, stack->element_size);
    stack->elements = (char *)stack->elements + stack->element_size;
}

void StackPop(stack_t *stack)
{
    assert(NULL != stack);
    stack->elements = (char *)stack->elements - stack->element_size;
}

void *StackPeek(const stack_t *stack)
{
    assert(NULL != stack);

    if (NULL == stack || StackIsEmpty(stack))
    {
        return NULL;
    }

    return (void *)((char *)stack->elements - stack->element_size);
}

int StackIsEmpty(const stack_t *stack)
{
    assert(NULL != stack);
    return (size_t)((char *)stack->elements - ((char *)stack + sizeof(stack_t))) == 0 ? 1 : 0;
}

size_t StackSize(const stack_t *stack)
{
    assert(NULL != stack);
    return (size_t)((char *)stack->elements - ((char *)stack + sizeof(stack_t))) / stack->element_size;
}

size_t StackCapacity(const stack_t *stack)
{
    assert(NULL != stack);
    return stack->capacity;
}
