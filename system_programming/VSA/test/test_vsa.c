

#include <stdio.h>
#include <stdlib.h>/*malloc*/

#include "vsa.h"




int main()
{	
	void *memory = (void *)malloc(80);
	vsa_t *vsa = VSAInit(memory, 80);
	
	
	VSAAlloc(vsa,32);
	VSAAlloc(vsa,16);
	if(VSAAlloc(vsa,16) == NULL)
	{
	
		puts("ERROR!");
	}
	

	free(memory);
return 0;
}
