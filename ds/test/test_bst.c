
#include <stdio.h>
#include "bst.h"



int Compare(const void *data, const void *key_data)
{
	return (int*)data - (int*)key_data;
}

int main()
{	
	
	bst_t *bst = BSTCreate(Compare);
	
	bst->root->childrens[LEFT] = ;
	

return 0;
}
