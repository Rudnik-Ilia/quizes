
#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "bst.h"



int Compare(const void *data, const void *key_data)
{
	return *(int*)data - *(int*)key_data;
}

int main()
{	
	bst_iter_t check_1 = NULL;	
	bst_iter_t check_2 = NULL;
	bst_iter_t check_3 = NULL;
	bst_iter_t check_4 = NULL;
	bst_iter_t check_5 = NULL;
	bst_iter_t check_6 = NULL;
	
	bst_iter_t max = NULL;
	
	int arr[] = {40, 30, 50, 20, 60, 70, 10};
	
	
	
	bst_t *bst = BSTCreate(Compare);
	TEST("Create, is empty", BSTIsEmpty(bst), 1);

	check_1 = BSTInsert(bst, &arr[0]);
	check_2 = BSTInsert(bst, &arr[1]);
	check_3 = BSTInsert(bst, &arr[2]);
	check_4 = BSTInsert(bst, &arr[3]);
	check_5 = BSTInsert(bst, &arr[4]);
	check_6 = BSTInsert(bst, &arr[6]);
	
	max = BSTInsert(bst, &arr[5]);
	
	
	TEST("Create, is empty", BSTIsEmpty(bst), 0);
	
	
	
	TEST("Test begin", *(int*)BSTGetData(BSTBegin(bst)), 10);
	
	TEST("Test begin", *(int*)BSTGetData(BSTNext(check_1)), 50);
	TEST("Test begin", *(int*)BSTGetData(BSTNext(check_2)), 40);
	TEST("Test begin", *(int*)BSTGetData(BSTNext(check_3)), 60);
	TEST("Test begin", *(int*)BSTGetData(BSTNext(check_4)), 30);
	TEST("Test begin", *(int*)BSTGetData(BSTNext(check_5)), 70);
	TEST("Test begin", *(int*)BSTGetData(BSTNext(check_6)), 20);
	
	TEST("Test begin", BSTNext(max), BSTEnd(bst));
	
	TEST("Test begin", *(int*)BSTGetData(BSTPrev(check_1)), 30);
	TEST("Test begin", *(int*)BSTGetData(BSTPrev(check_2)), 20);
	TEST("Test begin", *(int*)BSTGetData(BSTPrev(check_3)), 40);
	TEST("Test begin", *(int*)BSTGetData(BSTPrev(check_4)), 10);
	TEST("Test begin", *(int*)BSTGetData(BSTPrev(check_5)), 50);
	
	TEST("Test begin", *(int*)BSTGetData(BSTPrev(max)), 60);
	TEST("Test begin", *(int*)BSTGetData(BSTPrev(BSTEnd(bst))), 70);
	
	TEST("Test for size", BSTSize(bst), 7);
	
	TEST("Test for find", *(int*)BSTGetData(BSTFind(bst, &arr[0])), 40);
	TEST("Test for find", *(int*)BSTGetData(BSTFind(bst, &arr[1])), 30);
	TEST("Test for find", *(int*)BSTGetData(BSTFind(bst, &arr[2])), 50);
	TEST("Test for find", *(int*)BSTGetData(BSTFind(bst, &arr[3])), 20);
	TEST("Test for find", *(int*)BSTGetData(BSTFind(bst, &arr[4])), 60);
	TEST("Test for find", *(int*)BSTGetData(BSTFind(bst, &arr[5])), 70);
	
	
	
	/*
	
	
	*/
	


	
	
	free(bst);
	PASS;
return 0;
}
