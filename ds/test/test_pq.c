

#include <stdio.h>  /* printf */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "srtll.h"
#include "utils.h"
#include "test.h"
#include "dll.h"
#include "pqueue.h"

int CmpLowHigh(const void *new, const void *old)
{	
	return *(int*)new - *(int*)old;
}



int main()
{
	pq_t *pq = PQCreate(CmpLowHigh);
	
	
	
	
	PQDestroy(pq);




return 0;
}
