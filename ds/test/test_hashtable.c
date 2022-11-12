
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "test.h"

#define CAPACITY 10

size_t hash_function(const char* str) 
{
	size_t tmp = 0;
	size_t i = 0;

	for (i=0; str[i]; ++i)
	{
		tmp += str[i];
	}
	return tmp % CAPACITY;
}
 
size_t HashStr(const void *key) 
{
	char *str = (char*)key;
	size_t hash = CAPACITY;
	int c = 0;

	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c; 
	}
	return hash % CAPACITY;
}

int CompareStr(const void *p1, const void *p2)
{
	return !strcmp((char*)p1, (char*)p2);
}

int CompareInt(const void * p1, const void * p2)
{
	return *(int*)p1 == *(int*)p2;
}

int main()
{
	ht_t * ht = HTCreate(HashStr, 10, CompareStr);
	size_t i = 0;
	
	              /*   0        1         2           3          4         5         6         7           8         9         10    */
	char keys[][CAPACITY] = { "iliaaa", "rudnik", "batyam", "infini", "qwerty", "patric", "catdog", "greeny", "123456", "654321", "010101"};
	char values[][CAPACITY] = { "iliaaa", "rudnik", "batyam", "infini", "qwerty", "patric", "catdog", "greeny", "123456", "654321", "010101"};
	
	TEST("empty",HTIsEmpty(ht), 0);
	
	for(i = 0; i < CAPACITY; ++i)
	{
		HTInsert(ht, &keys[i] , &values[i]);
		TEST("Size in loop", HTSize(ht), i + 1);
	}
			
	TEST("empty",HTIsEmpty(ht), 1);		
			
	HTDestroy(ht);	
	PASS;		
return 0;
}
