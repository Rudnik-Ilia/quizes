

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
	
	arr[0] = VSAAlloc(vsa,16);
	assert(arr[0] != NULL && "111");
	
	arr[1] = VSAAlloc(vsa,16);
	assert(arr[1] != NULL && "222");
	
	arr[2] = VSAAlloc(vsa,8);
	assert(arr[2] != NULL && "333");
	
	
	
	
	VSAFree(arr[0]);
	VSAFree(arr[1]);
	
	VSAFree(arr[2]);
	/*
	arr[3] = VSAAlloc(vsa,8);
	assert(arr[3] != NULL && "444");
	VSAAlloc(vsa,8);
	printf("-----------------------------------\n");
	printf("%ld\n", *(long*)(char *)vsa);
	printf("%ld\n", *(long*)(char *)vsa + 24);
	printf("%ld\n", *(long*)(char *)vsa + 64);
	VSAFree(VSAAlloc(vsa,8));
	*/

	free(memory);
return 0;
}
