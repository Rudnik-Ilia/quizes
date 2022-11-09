#include <stdio.h>

#include "avl.h"
#include "test.h"



int Cmp(const void * p1, const void * p2)
{
	return (*(int*)p1 - *(int*)p2);
}

int main()
{
	int arr[] = {40, 30, 50, 20, 60, 70, 10};
	size_t size_arr = sizeof(arr)/sizeof(int);
	
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
	
/*	
	for(i = 0; i < size_arr; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
*/	
	
	printf("%ld\n", AVLHeight(avl));
	TEST("IsEmpty", AVLIsEmpty(avl), 0);
	

	TEST("FIND ", *(int*)AVLFind(avl, &arr[2]),arr[2]) ;
	
	
	PrintTree(avl);
	
	AVLDestroy(avl);
/*	
*/	
	



return 0;
}
