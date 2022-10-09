

#include <stdio.h>
#include <stdlib.h>/*malloc*/
#include <assert.h>

#include "vsa.h"




int main()
{	
	vsa_t * arr[4] = {0};
	void *memory = (void *)malloc(80);
	vsa_t *vsa = VSAInit(memory, 80);
	
	
	
	assert(VSAAlloc(vsa,16) != NULL && "first");
	printf("-----------------------------------\n");
	assert(VSAAlloc(vsa,40) != NULL && "second");
	printf("-----------------------------------\n");
	/*
	assert(VSAAlloc(vsa,8) != NULL && "third");
	printf("-----------------------------------\n");
	assert(VSAAlloc(vsa,8) != NULL && "fofth");
	*/
	

	free(memory);
return 0;
}
