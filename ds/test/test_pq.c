

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
	int arr[] = {10, 20, 30};
	
	TEST("IsEmpty after creater", PQIsEmpty(pq), 1);
	TEST("Size after creater", PQSize(pq), 0);
	
	PQEnqueue(pq, &arr[0]);
	PQEnqueue(pq, &arr[1]);
	
	TEST("Size after insert", PQSize(pq), 2);
	
	PQDequeue(pq);
	
	TEST("Size after insert", PQSize(pq), 1);
	
	PQEnqueue(pq, &arr[2]);
	printf("%d\n",*(int*)PQPeek(pq));
	
	PASS;
	
	PQDestroy(pq);

return 0;
}
