#include <stdlib.h>
#include <string.h>

#include "test.h"
#include "vsa.h"

#ifndef NDEBUG
#define HEADER_SIZE 16
#else
#define HEADER_SIZE 8
#endif

static void TestGeneral();

int main()
{
	TestGeneral();

	PASS;

	return 0;

}
static void TestGeneral()
{
	vsa_t *vsa = NULL;
	void *memory = NULL;
	size_t mem_size = 205;

	size_t largest_block = 200 - (2 * HEADER_SIZE);

	size_t block_sizes[5] = {20, 32, 100, 54, 34};
	void *blocks[5];

	char *str_arr[5];
	
	str_arr[0] = "block1";
	str_arr[1] = "block2";
	str_arr[2] = "block3";
	str_arr[3] = "block4";
	str_arr[4] = "block5";

	memory = (void *)malloc(mem_size);

	vsa = VSAInit(memory, mem_size);

	TEST("TESTING LargestBlock after Init", VSACheckLargestBlock(vsa), largest_block);

	blocks[0] = VSAAlloc(vsa, block_sizes[0]);
	largest_block -= block_sizes[0] + 4 + HEADER_SIZE;
	memcpy(blocks[0], str_arr[0], 7);
	
	TEST("TESTING LargestBlock after Alloc", VSACheckLargestBlock(vsa), largest_block);

	blocks[1] = VSAAlloc(vsa, block_sizes[1]);
	largest_block -= block_sizes[1] + HEADER_SIZE;
	memcpy(blocks[1], str_arr[1], 7);
	
	TEST("TESTING LargestBlock after Alloc", VSACheckLargestBlock(vsa), largest_block);

	#ifndef NDEBUG
	blocks[2] = VSAAlloc(vsa, block_sizes[2]);
	TEST("Testing Alloc without enough space", NULL == blocks[2], 1);
	#endif

	blocks[3] = VSAAlloc(vsa, block_sizes[3]);
	largest_block -= block_sizes[3] + 2 + HEADER_SIZE;
	memcpy(blocks[3], str_arr[3], 7);

	TEST("TESTING LargestBlock after Alloc", VSACheckLargestBlock(vsa), largest_block);

	VSAFree(blocks[1]);
	largest_block = 32;
	#ifdef NDEBUG
	largest_block += 16;
	#endif

	TEST("TESTING LargestBlock after Free", VSACheckLargestBlock(vsa), largest_block);
	
	VSAFree(blocks[0]);
	blocks[4] = VSAAlloc(vsa, block_sizes[4]);
	largest_block = (32 + 24 + HEADER_SIZE) - (HEADER_SIZE + 40);
	#ifdef NDEBUG
	largest_block += 32;
	#endif

	memcpy(blocks[4], str_arr[4], 7);
	
	TEST("TESTING LargestBlock after Free/Alloc", VSACheckLargestBlock(vsa), largest_block);

	TEST_STR("TESTING Data", (char *)blocks[4], str_arr[4]);
	TEST_STR("TESTING Data", (char *)blocks[3], str_arr[3]);

	free(memory);
}
