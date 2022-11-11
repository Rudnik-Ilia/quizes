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

void General();
void Find();
void Height();

int main()
{
	
	General();
	Find();
	Height();	
	
	
PASS;
return 0;
}

void Height()
{
	int arr[] = {40, 30, 50, 20, 60, 70, 10, 9, 8, 5, 4, 100, 80, 90};
	size_t size_arr = sizeof(arr)/sizeof(int);
	size_t i = 0;
	avl_t *avl = AVLCreate(Cmp);
	
	TEST("IsEmpty", AVLIsEmpty(avl), 1);
	TEST("HEIDHT", AVLHeight(avl), 0);
	TEST("Size", AVLSize(avl), 0);
	
	for(i = 0; i < size_arr; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	
	TEST("Find",*(int*)AVLFind(avl, &arr[9]), arr[9]);
	AVLRemove(avl, &arr[9]);
	TEST("Find", AVLFind(avl, &arr[9]), NULL); 
	
	TEST("Find",*(int*)AVLFind(avl, &arr[0]), arr[0]);
	AVLRemove(avl, &arr[0]);
	TEST("Find", AVLFind(avl, &arr[0]), NULL); 
	
	TEST("Find",*(int*)AVLFind(avl, &arr[2]), arr[2]);
	AVLRemove(avl, &arr[2]);
	TEST("Find", AVLFind(avl, &arr[2]), NULL); 
	
	TEST("Size", AVLSize(avl), 11);
	TEST("HEIDHT", AVLHeight(avl), 4);
	
	AVLRemove(avl, &arr[1]);
	AVLRemove(avl, &arr[6]);
	AVLRemove(avl, &arr[10]);
	AVLRemove(avl, &arr[13]);
	TEST("HEIDHT", AVLHeight(avl), 3);
	TEST("Size", AVLSize(avl), 7);
	
	AVLRemove(avl, &arr[8]);
	AVLRemove(avl, &arr[3]);
	AVLRemove(avl, &arr[5]);
	AVLRemove(avl, &arr[11]);
	TEST("HEIDHT", AVLHeight(avl), 2);
	TEST("Size", AVLSize(avl), 3);
	
	AVLRemove(avl, &arr[4]);
	AVLRemove(avl, &arr[12]);
	TEST("HEIDHT", AVLHeight(avl), 1);
	TEST("Size", AVLSize(avl), 1);
	
	TEST("Find",*(int*)AVLFind(avl, &arr[7]), arr[7]);
	AVLDestroy(avl);
}

void Find()
{
	int arr[] = {40, 30, 50, 20, 60, 70, 10, 9, 8, 5, 4, 100, 80, 90};
	
	int test[] = {40, 30, 50, 20, 60, 70, 10, 9, 8, 5, 4, 100, 80, 90};
	size_t size_arr = sizeof(arr)/sizeof(int);
	int factor = 2;
	size_t i = 0;
	
	avl_t *avl = AVLCreate(Cmp);
	
	TEST("IsEmpty", AVLIsEmpty(avl), 1);
	TEST("HEIDHT", AVLHeight(avl), 0);
	TEST("Size", AVLSize(avl), 0);
	
	for(i = 0; i < size_arr; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	
	TEST("Preorder",AVLForEach(avl, Act, &factor, PRE_ORDER), 0);
	
	for(i = 0; i < size_arr; ++i)
	{
		TEST("Find",*(int*)AVLFind(avl, &arr[i]), test[i]*2); 
	}
	
	TEST("Postorder",AVLForEach(avl, Act, &factor, POST_ORDER), 0);
	
	
	for(i = 0; i < size_arr; ++i)
	{
	 	
		TEST("Find",*(int*)AVLFind(avl, &arr[i]), test[i]*4); 
	}
	
	TEST("Inorder",AVLForEach(avl, Act, &factor, IN_ORDER), 0);
	
	for(i = 0; i < size_arr; ++i)
	{
	 	
		TEST("Find",*(int*)AVLFind(avl, &arr[i]), test[i]*8); 
	}
	
	TEST("Preorder",AVLForEach(avl, Act, &factor, IN_ORDER), 0);
	TEST("Preorder",AVLForEach(avl, Act, &factor, IN_ORDER), 0);
	
	for(i = 0; i < size_arr; ++i)
	{
	 	
		TEST("Find", AVLFind(avl, &test[i]), NULL); 
	}
	AVLDestroy(avl);
}


void General()
{
		  /*  0   1   2   3   4   5   6  7  8  9  10  11  12   13 */
	int arr[] = {40, 30, 50, 20, 60, 70, 10, 9, 8, 5, 4, 100, 80, 90};
	
	size_t size_arr = sizeof(arr)/sizeof(int);
	size_t i = 0;
	
	avl_t *avl = AVLCreate(Cmp);
	
	TEST("IsEmpty", AVLIsEmpty(avl), 1);
	TEST("HEIDHT", AVLHeight(avl), 0);
	TEST("Size", AVLSize(avl), 0);
	
	for(i = 0; i < size_arr; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	
	TEST("IsEmpty", AVLIsEmpty(avl), 0);
	TEST("HEIDHT", AVLHeight(avl), 4);
	TEST("Size", AVLSize(avl), 14);
	
	AVLRemove(avl, &arr[0]);
	TEST("Size", AVLSize(avl), 13);
	
	AVLRemove(avl, &arr[10]);
	AVLRemove(avl, &arr[13]);
	TEST("Size", AVLSize(avl), 11);
	
	AVLRemove(avl, &arr[2]);
	TEST("Size", AVLSize(avl), 10);
	
	AVLRemove(avl, &arr[12]);
	AVLRemove(avl, &arr[3]);
	TEST("Size", AVLSize(avl), 8);
	
	AVLRemove(avl, &arr[5]);
	TEST("Size", AVLSize(avl), 7);
	
	AVLRemove(avl, &arr[9]);
	AVLRemove(avl, &arr[1]);
	TEST("Size", AVLSize(avl), 5);
	
	AVLRemove(avl, &arr[8]);
	AVLRemove(avl, &arr[6]);
	TEST("Size", AVLSize(avl), 3);
	
	AVLRemove(avl, &arr[4]);
	TEST("Size", AVLSize(avl), 2);
	
	AVLRemove(avl, &arr[11]);
	AVLRemove(avl, &arr[7]);
	
	TEST("Size", AVLSize(avl), 0);
	
	AVLDestroy(avl);
}
