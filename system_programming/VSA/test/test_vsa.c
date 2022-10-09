

#include <stdio.h>
#include <stdlib.h>/*malloc*/
#include <assert.h>

#include "vsa.h"




int main()
{	
	vsa_t * arr[4] = {0};
	void *memory = (void *)malloc(100);
	vsa_t *vsa = VSAInit(memory, 100);
	block_t * block = vsa;
	
	
	
	assert(VSAAlloc(vsa,16) != NULL && "111");
	printf("-----------------------------------\n");
	assert(VSAAlloc(vsa,32) != NULL && "222");
	printf("-----------------------------------\n");
	assert(VSAAlloc(vsa,8) != NULL && "333");
	/*
	assert(VSAAlloc(vsa,8) != NULL && "444");
	VSAAlloc(vsa,8);
	printf("-----------------------------------\n");
	printf("%ld\n", *(long*)(char *)vsa);
	printf("%ld\n", *(long*)(char *)vsa + 24);
	printf("%ld\n", *(long*)(char *)vsa + 64);
	printf("%d\n",Next(block)->size);
	*/

	free(memory);
return 0;
}
