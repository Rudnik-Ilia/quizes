
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "test.h"

#define CAPACITY 11

size_t HashFuncStr(const void *key) 
{	
	char *str = (char*)key;
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
	size_t hash = 513284950;
	int c = 0;

	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c; 
	}
	return hash % CAPACITY;
}

size_t hash(const void *str) { 

    const int ret_size = CAPACITY;
    char *input = (char*)str;
    size_t ret = 0x555555;
    const int per_char = 7;

    while (*input) { 
        ret ^= *input++;
        ret = (ret << per_char) | (ret >> (ret_size - per_char));
   }
   return ret % CAPACITY;
}

int CompareStr(const void *p1, const void *p2);
int CompareStr(const void *p1, const void *p2);
void Gemeral();

int main()
{
	ht_t * ht = HTCreate(HashFuncStr, CAPACITY, CompareStr);
	size_t i = 0;
	/********collis              4        4         0          10         2         5        10         1         1        1        5
	         */
	                        /*   0        1         2           3         4         5         6         7           8        9      10    */
	char keys[][CAPACITY] = { "iliaaa", "rudnik", "batyam", "infini", "qwerty", "patric", "catdog", "greeny", "123456", "654321", "010101"};
	char values[][CAPACITY] = { "aaaaaa", "bbbbbb", "cccccc", "ffffff", "eeeeee", "gggggg", "hhhhhh", "iiiiii", "000000", "777777", "111111"};
	
	TEST("empty",HTIsEmpty(ht), 0);
	
	HTInsert(ht, &keys[0] , &values[0]);
	HTInsert(ht, &keys[1] , &values[1]);
	HTInsert(ht, &keys[2] , &values[2]);
	HTInsert(ht, &keys[3] , &values[3]);
	HTInsert(ht, &keys[4] , &values[4]);
	
	TEST("Size", HTSize(ht), 5);
	
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[0]), values[0]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[1]), values[1]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[2]), values[2]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[3]), values[3]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[4]), values[4]), 0);

	HTInsert(ht, &keys[0] , &values[10]);
	HTInsert(ht, &keys[1] , &values[9]);
	HTInsert(ht, &keys[2] , &values[8]);
	HTInsert(ht, &keys[3] , &values[7]);
	
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[0]), values[10]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[1]), values[9]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[2]), values[8]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[3]), values[7]), 0);
	
	TEST("Size", HTSize(ht), 5);
	HTDestroy(ht);
/*
	Gemeral();
*/	
	PASS;		
return 0;
}

void Gemeral()
{
	ht_t * ht = HTCreate(HashFuncStr, CAPACITY, CompareStr);
	size_t i = 0;
	/********collis              4        4         0          10         2         5        10         1         1        1        5
	         */
	                        /*   0        1         2           3         4         5         6         7           8        9      10    */
	char keys[][CAPACITY] = { "iliaaa", "rudnik", "batyam", "infini", "qwerty", "patric", "catdog", "greeny", "123456", "654321", "010101"};
	char values[][CAPACITY] = { "aaaaaa", "bbbbbb", "cccccc", "ffffff", "eeeeee", "gggggg", "hhhhhh", "iiiiii", "000000", "777777", "111111"};
	
	TEST("empty",HTIsEmpty(ht), 0);
	
	HTInsert(ht, &keys[0] , &values[0]);
	HTInsert(ht, &keys[1] , &values[1]);
	HTInsert(ht, &keys[2] , &values[2]);
	HTInsert(ht, &keys[3] , &values[3]);
	HTInsert(ht, &keys[4] , &values[4]);
	HTInsert(ht, &keys[5] , &values[5]);
	HTInsert(ht, &keys[6] , &values[6]);
	HTInsert(ht, &keys[7] , &values[7]);
	HTInsert(ht, &keys[8] , &values[8]);
	HTInsert(ht, &keys[9] , &values[9]);
	HTInsert(ht, &keys[10] , &values[10]);
	
	TEST("Size", HTSize(ht), 11);

	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[0]), values[0]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[1]), values[1]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[2]), values[2]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[3]), values[3]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[4]), values[4]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[5]), values[5]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[6]), values[6]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[7]), values[7]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[8]), values[8]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[9]), values[9]), 0);
	TEST("Find ",  strcmp((char*)HTFind(ht, &keys[10]), values[10]), 0);
	
	TEST("empty",HTIsEmpty(ht), 1);
	
	HTRemove(ht, &keys[0]);
	TEST("Find after remove", HTFind(ht, &keys[0]),  NULL);
	TEST("Size", HTSize(ht), 10);
	
	for(i = 1; i < CAPACITY; ++i)
	{
		HTRemove(ht, &keys[i]);
		TEST("Size while remove", HTSize(ht), 10 - i);
		
	}
	TEST("empty",HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 0);
	
	HTDestroy(ht);	
}

int CompareStr(const void *p1, const void *p2)
{
	return !strcmp((char*)p1, (char*)p2);
}

int CompareInt(const void * p1, const void * p2)
{
	return *(int*)p1 == *(int*)p2;
}

