
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
	ht_t * ht = HTCreate(HashFuncStr, CAPACITY, CompareStr);
	size_t i = 0;
	/********collis              9        1         2          9           0         5         2         0        2          5       7
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
	
	for(i = 0; i < CAPACITY; ++i)
	{
		printf("%ld ", HashStr(&keys[i])); 
	}
			
	/*
	
	
	
	for(i = 0; i < CAPACITY; ++i)
	{
		printf("%s\n", (char*)HTFind(ht,&keys[i]));
	}
	*/
	printf("%s\n",  (char*)HTFind(ht, &keys[0]));
	printf("%s\n",  (char*)HTFind(ht, &keys[1]));
	printf("%s\n",  (char*)HTFind(ht, &keys[2]));
	printf("%s\n",  (char*)HTFind(ht, &keys[3]));
	printf("%s\n",  (char*)HTFind(ht, &keys[4]));
	printf("%s\n",  (char*)HTFind(ht, &keys[4]));
	
	
	printf("%s\n",  (char*)HTFind(ht, &keys[6]));
	/*

	*/
	
	HTDestroy(ht);	
	
	PASS;		
return 0;
}
