
#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "bst.h"



int Compare(const void *data, const void *key_data)
{
	return (int*)data - (int*)key_data;
}

int main()
{		
	bst_iter_t a = NULL;
	int arr[] = {40, 30, 50, 20, 60, 70, 10};
	
	
	
	bst_t *bst = BSTCreate(Compare);
	TEST("Create, is empty", BSTIsEmpty(bst), 1);

	BSTInsert(bst, &arr[3]);
	BSTInsert(bst, &arr[1]);
	BSTInsert(bst, &arr[4]);
	BSTInsert(bst, &arr[2]);
	BSTInsert(bst, &arr[0]);
	BSTInsert(bst, &arr[5]);
	BSTInsert(bst, &arr[6]);
	
	TEST("Create, is empty", BSTIsEmpty(bst), 0);
	a = BSTBegin(bst);
	
	TEST("Test begin", *(int*)BSTGetData(a), arr[6]);
	
	
	


	
	
	free(bst);
	PASS;
return 0;
}
