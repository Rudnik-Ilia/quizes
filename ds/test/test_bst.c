
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"



int Compare(const void *data, const void *key_data)
{
	return (int*)data - (int*)key_data;
}

int main()
{	
	
	
	bst_t *bst = BSTCreate(Compare);
	
	
	free(bst);
return 0;
}
