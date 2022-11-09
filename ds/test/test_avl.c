#include <stdio.h>

#include "avl.h"
#include "test.h"



int Cmp(const void * p1, const void * p2)
{
	return (*(int*)p1 - *(int*)p2);
}
int Act(void *data, void *params)
{

	*(int*)data *= *(int*)params;
	return 0;
}

int main()
{
	int arr[] = {40, 30, 50, 20, 60, 70, 10,55, 25};
	size_t size_arr = sizeof(arr)/sizeof(int);
	int factor = 2;
	size_t i = 0;
	avl_t *avl = AVLCreate(Cmp);
	TEST("IsEmpty", AVLIsEmpty(avl), 1);
	printf("%ld\n", AVLHeight(avl));
	
	AVLInsert(avl, &arr[0]);
	AVLInsert(avl, &arr[1]);
	AVLInsert(avl, &arr[2]);
	AVLInsert(avl, &arr[3]);
	AVLInsert(avl, &arr[4]);
	AVLInsert(avl, &arr[5]);
	AVLInsert(avl, &arr[6]);
	AVLInsert(avl, &arr[7]);
	AVLInsert(avl, &arr[8]);
/*	
	AVLInsert(avl, &arr[9]);
	AVLInsert(avl, &arr[10]);
	AVLInsert(avl, &arr[11]);
	AVLInsert(avl, &arr[12]);
	AVLInsert(avl, &arr[13]);
	
	for(i = 0; i < size_arr; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, Act, &arr[1], PRE_ORDER);
	printf("\n");
	AVLForEach(avl, Act, &arr[1], POST_ORDER);
	printf("\n");
*/	
	printf("SIZE: %ld\n",AVLSize(avl));
	printf("%ld\n", AVLHeight(avl));
	TEST("IsEmpty", AVLIsEmpty(avl), 0);
	TEST("FIND ", *(int*)AVLFind(avl, &arr[2]),arr[2]) ;
	
	AVLRemove(avl, &arr[7]);
	PrintTree(avl);
	/*
	AVLRemove(avl, &arr[8]);
	AVLRemove(avl, &arr[1]);
	AVLRemove(avl, &arr[6]);
	AVLRemove(avl, &arr[3]);
	AVLRemove(avl, &arr[5]);
	AVLForEach(avl, Act, &factor, POST_ORDER);
	printf("\n");

	
	
	PrintTree(avl);
	printf("SIZE: %ld\n",AVLSize(avl));
	*/
	
	
	
	AVLDestroy(avl);
/*	
*/	
	



return 0;
}
