#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "fsa.h"

static void TestGeneral();

int main()
{
	TestGeneral();
	PASS;

	return 0;
}

static void TestGeneral()
{
	void *memory = NULL;
	fsa_t *fsa = NULL;

	size_t i = 0;

	size_t pos_arr[5] = {8, 24, 40, 56, 72};
	int rand_i_arr[5] = {3, 0, 2, 1, 4};
	size_t rand_pos_arr[5] = {72, 24, 40, 8, 56};
	size_t rand_next_arr[5] = {24, 40, 8, 56, 0};

	void *blocks[5];
	size_t blocks_size = sizeof(blocks) / sizeof(void *);

	size_t mem_size = 0;
	size_t block_size = 9;
	size_t nr_of_blocks = 5;

	char *str_arr[5];

	str_arr[0] = "block1";
	str_arr[1] = "block2";
	str_arr[2] = "block3";
	str_arr[3] = "block4";
	str_arr[4] = "block5";


	/********** Testing suggestions / recalculation **********/
	TEST("TESTING FSASuggestSize",FSASuggestSize(7, 1), 64);

	TEST("TESTING FSASuggestSize",FSASuggestSize(7, 7), 64); 
	TEST("TESTING FSASuggestSize",FSASuggestSize(7, 8), 64); 
	TEST("TESTING FSASuggestSize",FSASuggestSize(7, 9), 120); 
	
	TEST("TESTING FSASuggestSize",FSASuggestSize(7, 15), 120); 

	mem_size = FSASuggestSize(nr_of_blocks, block_size);

	memory = (void *)malloc(mem_size);

	if(NULL == memory)
	{
		return;
	}
	
	/********** Testing Init and Allocation **********/

	fsa = FSAInit(memory, mem_size, block_size);

	for(; i < blocks_size; ++i)
	{
		TEST("TESTING FSACountFree/Alloc",FSACountFree(fsa), blocks_size - i);	
		blocks[i] = FSAAlloc(fsa);
	}
	
	TEST("TESTING FSACountFree",FSACountFree(fsa), 0);	

	for(i = 0; i < blocks_size; ++i)
	{
		TEST("TESTING block-positions after FSAInit/FSAAlloc",
		(size_t)blocks[i] - (size_t)fsa, pos_arr[i]);	
	
		TEST("TESTING block-next after FSAInitAlloc",
		*(size_t *)blocks[i], (pos_arr[i] + 16) % 88);
	
		memcpy(blocks[i], str_arr[i], 7);		
	}


	/********** Testing Free random order and new values **********/
	for(i = 0; i < blocks_size; ++i)
	{
		TEST_STR("TESTING added content", (char *)blocks[rand_i_arr[i]], str_arr[rand_i_arr[i]]);
		FSAFree(fsa, blocks[rand_i_arr[i]]);
		TEST("TESTING FSACountFree while Free",FSACountFree(fsa), i + 1);	
	}
	
	for(i = 0; i < blocks_size; ++i)
	{
		TEST("TESTING FSACountFree/Alloc after FSAFree",FSACountFree(fsa), blocks_size - i);	
		blocks[i] = FSAAlloc(fsa);
	}

	for(i = 0; i < blocks_size; ++i)
	{
		TEST("TESTING block-positions after FSAFree/Alloc",
		(size_t)blocks[i] - (size_t)fsa, rand_pos_arr[i]);	
	
		TEST("TESTING block-next after FSAFree/Alloc",
		*(size_t *)blocks[i], rand_next_arr[i]);
	}

	free(memory);	
}
