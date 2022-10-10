

#include <stdio.h>
#include <stdlib.h>/*malloc*/
#include <assert.h>

#include "vsa.h"


block_t *Next(block_t *block);

int main()
{	
	void * arr[4];
	void *memory = (void *)malloc(100);
	vsa_t *vsa = VSAInit(memory, 100);
	
	printf("%ld\n", VSACheckLargestBlock(vsa));
	
	arr[0] = VSAAlloc(vsa,32);
	assert(arr[0] != NULL && "111");
	
	printf("%ld\n", VSACheckLargestBlock(vsa));
	
	arr[1] = VSAAlloc(vsa,8);
	assert(arr[1] != NULL && "222");
	
	arr[2] = VSAAlloc(vsa,8);
	assert(arr[2] != NULL && "333");
	
	VSAFree(arr[1]);
	printf("%ld\n", VSACheckLargestBlock(vsa));
	VSAFree(arr[2]);
	
	printf("%ld\n", VSACheckLargestBlock(vsa));
	
	
	arr[3] = VSAAlloc(vsa,16);
	assert(arr[3] != NULL && "444");
	
	assert(VSAAlloc(vsa,8) != NULL && "555");
	VSAFree(arr[0]);
	printf("%ld\n", VSACheckLargestBlock(vsa));
	assert(VSAAlloc(vsa,24) != NULL && "666");
	printf("%ld\n", VSACheckLargestBlock(vsa));
	/*
	assert(VSAAlloc(vsa,24) != NULL && "777");
	VSAAlloc(vsa,8);
	VSAFree(arr[0]);
	
	VSAFree(arr[0]);
	printf("-----------------------------------\n");
	printf("%ld\n", *(long*)(char *)vsa);
	printf("%ld\n", *(long*)(char *)vsa + 24);
	printf("%ld\n", *(long*)(char *)vsa + 64);
	VSAFree(VSAAlloc(vsa,8));
	*/

	free(memory);
return 0;
}
