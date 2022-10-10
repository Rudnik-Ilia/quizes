

#include <stdio.h>
#include <stdlib.h>/*malloc*/
#include <assert.h>

#include "vsa.h"
#include "test.h"

void Basic_Test();
void Special_One();
void Special_Two();

int main()
{	
	Basic_Test();
	Special_One();
	Special_Two();
	
	/*

	*/
	PASS;
	
return 0;
}
void Special_Two()
{
	void * arr[3];
	
	void *memory = (void *)malloc(200);
	vsa_t *vsa = VSAInit(memory, 200);
	
	TEST("CheckLargestBlock after init", VSACheckLargestBlock(vsa), 168);
	
	arr[0] = VSAAlloc(vsa,32);
	assert(arr[0] != NULL);
	arr[1] = VSAAlloc(vsa,32);
	assert(arr[0] != NULL);
	arr[2] = VSAAlloc(vsa,32);
	assert(arr[0] != NULL);
	
	TEST("CheckLargestBlock after init", VSACheckLargestBlock(vsa), 24);
	
	VSAFree(arr[0]);
	
	VSAFree(arr[1]);
	/*
	*/
	VSAFree(arr[1]);
	
	 
	TEST("CheckLargestBlock after the same action", VSACheckLargestBlock(vsa), 80);
	
	TEST("CheckLargestBlock after the same action", VSACheckLargestBlock(vsa), 80);
	
	
	
	
}
void Special_One()
{
	void * arr[3];
	size_t i = 0;
	
	
	void *memory = (void *)malloc(200);
	vsa_t *vsa = VSAInit(memory, 200);
	
	TEST("CheckLargestBlock after init", VSACheckLargestBlock(vsa), 168);
	
	arr[0] = VSAAlloc(vsa,32);
	assert(arr[0] != NULL);
	arr[1] = VSAAlloc(vsa,32);
	assert(arr[0] != NULL);
	arr[2] = VSAAlloc(vsa,32);
	assert(arr[0] != NULL);
	
	TEST("CheckLargestBlock end", VSACheckLargestBlock(vsa), 24);
	
	
	for(; i < 3; ++i) VSAFree(arr[i]);
	
	TEST("CheckLargestBlock after free all", VSACheckLargestBlock(vsa), 168);
	
	free(memory);
}

void Basic_Test()
{

	void * arr[5];
	
	void *memory = (void *)malloc(300);
	vsa_t *vsa = VSAInit(memory, 300);
	
	TEST("CheckLargestBlock after init", VSACheckLargestBlock(vsa), 264);
	
	arr[0] = VSAAlloc(vsa,32);
	assert(arr[0] != NULL && "111");
	
	TEST("CheckLargestBlock alloc 32", VSACheckLargestBlock(vsa), 216);
	
	arr[1] = VSAAlloc(vsa,8);
	assert(arr[1] != NULL && "222");
	
	TEST("CheckLargestBlock alloc 8", VSACheckLargestBlock(vsa), 192);
	
	arr[2] = VSAAlloc(vsa,8);
	assert(arr[2] != NULL && "333");
	
	VSAFree(arr[1]);
	TEST("CheckLargestBlock alloc 8 free 8", VSACheckLargestBlock(vsa), 168);
	
	VSAFree(arr[2]);
	
	TEST("CheckLargestBlock alloc free 8", VSACheckLargestBlock(vsa), 216);
	
	arr[3] = VSAAlloc(vsa,16);
	assert(arr[3] != NULL && "444");
	
	assert(VSAAlloc(vsa,24) != NULL && "555");
	VSAFree(arr[0]);
	
	TEST("CheckLargestBlock alloc 16, 24", VSACheckLargestBlock(vsa), 144);
	/*
	arr[4] = VSAAlloc(vsa,24);
	assert(arr[4] != NULL && "555");
	
	TEST("CheckLargestBlock strange behavior ", VSACheckLargestBlock(vsa), 0);
	*/
	
	arr[4] = VSAAlloc(vsa,50);
	assert(arr[4] != NULL && "666");
	
	TEST("CheckLargestBlock after alloc 50", VSACheckLargestBlock(vsa), 72);
	
	free(memory);
}
