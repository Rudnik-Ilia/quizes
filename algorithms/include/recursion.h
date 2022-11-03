#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>

#include "../../ds/include/stack.h"

typedef struct node
{
	int data;
	struct node *next;
	
} node_t;

int FibRec(int idx);

int FibIter(int idx);

node_t *ListFlip(node_t *head);

void StackSort(stack_t *stack);



/* String funcs */
size_t StrLen(const char *str);
int StrCmp(const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);

#endif /* __RECURSION_H__ */
