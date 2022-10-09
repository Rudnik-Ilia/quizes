

#include <stdio.h>
#include <stdlib.h>/*malloc*/

#include "vsa.h"




int main()
{	
	void *memory = (void *)malloc(100);
	vsa_t *vsa = VSAInit(memory, 100);


return 0;
}
