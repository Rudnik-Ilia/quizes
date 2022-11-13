
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <string.h>

#include "hash_table.h"
#include "test.h"

#define CAPACITY 11
#define SIZE_DICT 110000


size_t HashFuncStr(const void *key); 
size_t HashFuncStrBig(const void *key); 
int Action(void *data, void *data1);
int CompareStr(const void *p1, const void *p2);
int CompareStr(const void *p1, const void *p2);
void Gemeral();
void Rewrite();
void Foreach();
void Dict();

int main()
{	
	
	Gemeral();
	Rewrite();
	Foreach();
	Dict();
	
	PASS;		
return 0;
}

void Dict()
{	
	char arr[SIZE_DICT][50]; 
	size_t i = 0;
	char word[50];
	
	ht_t * ht = HTCreate(HashFuncStrBig, SIZE_DICT, CompareStr);
	
	FILE * file = fopen("/usr/share/dict/words", "r");
	if(NULL == file)
	{
		return;
	}
	while(fscanf(file, "%s", &arr[i][0]) != EOF)
	{
		HTInsert(ht, &arr[i], &i);
		++i;
	}
	fclose(file);
	
	while(strcmp(word, "q"))
	{
		printf("Insert the word: (for exit press 'q' )\n");
		scanf("%s", word);
		if(HTFind(ht, word) == NULL)
		{
			printf("NO!\n");
		}
		else
		{
			printf("YES!\n");
		}
	}
        HTDestroy(ht);
}


void Foreach()
{
	ht_t * ht = HTCreate(HashFuncStr, CAPACITY, CompareStr);
	
	char keys[][CAPACITY] = { "iliaaa", "rudnik", "batyam", "infini", "qwerty", "patric", "catdog", "greeny", "123456", "654321", "010101"};
	int values[CAPACITY] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000 };
	int valuesInt[CAPACITY] = { 101, 201, 301, 401, 501, 601, 701, 801, 901, 1001, 2001 };
	int p = 1;
	TEST("empty",HTIsEmpty(ht), 0);
	
	HTInsert(ht, &keys[0] , &values[0]);
	HTInsert(ht, &keys[1] , &values[1]);
	HTInsert(ht, &keys[2] , &values[2]);
	HTInsert(ht, &keys[3] , &values[3]);
	HTInsert(ht, &keys[4] , &values[4]);
	
	TEST("Size", HTSize(ht), 5);
	HTForEach(ht, Action, &p);
	
	TEST("Find ", *(int*)HTFind(ht, &keys[0]), valuesInt[0]);
	TEST("Find ", *(int*)HTFind(ht, &keys[1]), valuesInt[1]);
	TEST("Find ", *(int*)HTFind(ht, &keys[2]), valuesInt[2]);
	TEST("Find ", *(int*)HTFind(ht, &keys[3]), valuesInt[3]);
	TEST("Find ", *(int*)HTFind(ht, &keys[4]), valuesInt[4]);
	HTDestroy(ht);
	
}

void Rewrite()
{
	ht_t * ht = HTCreate(HashFuncStr, CAPACITY, CompareStr);
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

size_t HashFuncStrBig(const void *key) 
{	
	char *str = (char*)key;
	size_t tmp = 0;
	size_t i = 0;

	for (i=0; str[i]; ++i)
	{
		tmp += str[i];
	}
	return tmp %  SIZE_DICT;
}
 
int Action(void *data, void *data1)
{
	assert(NULL != data);
	assert(NULL != data1);
	
	*(int*)data += *(int*)data1;
	
	return 0;
}
