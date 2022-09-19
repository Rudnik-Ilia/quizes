#include "test.h"
#include "vector.h"
#include "dll.h"

static void TestDLLGeneral();
static void TestMultiFind();
static void TestSplice();
static void TestRemove();


static int IsMatchInt(const void *data, void *param);
int main()
{
	TestDLLGeneral();
	TestMultiFind();
	TestSplice();


	return 0;
}

static void TestRemove()
{
	int a = 12;
	int b = 67;
	int c = 555;
	int d = 666;
	int e = 8008;

	dllist_t *dll = DLLCreate();

	DLLPushFront(dll, &a);
	DLLPushFront(dll, &b);
	DLLPushFront(dll, &c);
	DLLPushFront(dll, &d);/*
	DLLPushFront(dll, &e);
*/
	DLLDestroy(dll);

}

static void TestDLLGeneral()
{
	int arr[] = {11, 9001, 404, 69, 120, 40, 80085, 13, 99, 2077};
	int arr_manipulated[] = {11, 9001, 404, 55, 69, 40, 101, 80085, 99, 2077};
	
	int insert1 = 55;
	int insert2 = 101;

	size_t arr_size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	void *data = NULL;

	dllist_iter_t iter = NULL;

	dllist_t *dll = NULL;

	dll = DLLCreate();

	TEST("TESTING Create", NULL != dll, 1);
	if(NULL == dll)
	{
		return;
	}

	TEST("TESTING IsEmpty - after create", DLLIsEmpty(dll), 1);
	TEST("TESTING Size - after create", DLLSize(dll), 0);


	/********** PUSH/POP FRONT **********/
	
	iter = DLLBegin(dll);
	for(; i < arr_size; ++i)
	{
		iter = DLLPushFront(dll, &arr[i]);
		TEST("TESTING PushFront", NULL != iter, 1);
		TEST("TESTING Size - while PushFront", DLLSize(dll), i + 1);
		if(NULL == iter)
		{
			return;
		}
	}

	TEST("TESTING IsEmpty - after PushFront", DLLIsEmpty(dll), 0);
	TEST("TESTING Size - after PushFront", DLLSize(dll), arr_size);
	
	for(i = arr_size -1; !DLLIsEmpty(dll); --i)
	{
		data = DLLPopFront(dll);
		TEST("TESTING PopFront", NULL != data, 1);
		if(NULL == data)
		{
			return;
		}
		TEST("TESTING PopFront", *(int *)data, arr[i]);
	}
	
	TEST("TESTING IsEmpty - after PopFront", DLLIsEmpty(dll), 1);
	TEST("TESTING Size - after PopFront", DLLSize(dll), 0);

	/********** PUSH/POP BACK **********/
	
	iter = DLLBegin(dll);
	for(i = 0; i < arr_size; ++i)
	{
		iter = DLLPushBack(dll, &arr[i]);
		TEST("TESTING PushBack", NULL != iter, 1);
		TEST("TESTING Size - while PushBack", DLLSize(dll), i + 1);
		if(NULL == iter)
		{
			return;
		}
	}
	TEST("TESTING IsEmpty - after PushBack", DLLIsEmpty(dll), 0);
	TEST("TESTING Size - after PushBack", DLLSize(dll), arr_size);
	
	for(i = arr_size - 1; !DLLIsEmpty(dll); --i)
	{
		data = DLLPopBack(dll);
		TEST("TESTING PopBack", NULL != data, 1);
		if(NULL == data)
		{
			return;
		}
		TEST("TESTING PopBack", *(int *)data, arr[i]);
	}
	
	TEST("TESTING IsEmpty - after PopBack", DLLIsEmpty(dll), 1);
	TEST("TESTING Size - after PopBack", DLLSize(dll), 0);

	/********** INSERT / REMOVE / GET / SET **********/
	
	iter = DLLBegin(dll);
	for(i = 0; i < arr_size; ++i)
	{
		iter = DLLInsert(iter, &arr[i]);
		TEST("TESTING Insert", NULL != iter, 1);
		TEST("TESTING Size - while Insert", DLLSize(dll), i + 1);
		if(NULL == iter)
		{
			return;
		}
		iter = DLLNext(iter);
	}
	TEST("TESTING IsEmpty - after Insert", DLLIsEmpty(dll), 0);
	TEST("TESTING Size - after Insert", DLLSize(dll), arr_size);
	
	iter = DLLBegin(dll);
	for(i = 0; i < arr_size; ++i, iter = DLLNext(iter))
	{
		TEST("TESTING GetData/Next - after insert", *(int *)DLLGetData(iter), arr[i]);
	}
	
	iter = DLLEnd(dll);
	iter = DLLPrev(iter);
	for(i = arr_size; i > 0; --i,iter = DLLPrev(iter))
	{
		TEST("TESTING GetData/Prev - after insert", *(int *)DLLGetData(iter), arr[i - 1]);
	}

	arr_manipulated[0] = 70;

	iter = DLLBegin(dll);
	DLLSetData(iter, &arr_manipulated[0]);
	iter = DLLNext(iter);
	iter = DLLNext(iter);
	iter = DLLNext(iter);
	iter = DLLInsert(iter, &insert1);
	TEST("TESTING Size - after one insert", DLLSize(dll), arr_size + 1);

	iter = DLLNext(iter);
	arr_manipulated[4] = 9999;
	DLLSetData(iter, &arr_manipulated[4]);	

	iter = DLLNext(iter);
	iter = DLLRemove(iter);	
	TEST("TESTING Size - after one remove", DLLSize(dll), arr_size);

	iter = DLLNext(iter);
	iter = DLLInsert(iter, &insert2);
	TEST("TESTING Size - after one insert", DLLSize(dll), arr_size + 1);
	
	iter = DLLNext(iter);
	iter = DLLNext(iter);	
	DLLRemove(iter);
	TEST("TESTING Size - after one remove", DLLSize(dll), arr_size);
	
	iter = DLLBegin(dll);
	for(i = 0; i < arr_size; ++i, iter = DLLNext(iter))
	{
		TEST("TESTING Get Data -  after insert/remove and set data in middle", *(int *)DLLGetData(iter), arr_manipulated[i]);
	}

	iter = DLLFind(DLLBegin(dll), DLLEnd(dll), IsMatchInt, &arr_manipulated[4]);
	TEST("TESTING Find", DLLIsEqualIter(iter, DLLEnd(dll)), 0); 
	TEST("TESTING Find", *(int *)DLLGetData(iter), arr_manipulated[4]);

	iter = DLLFind(DLLBegin(dll), DLLEnd(dll), IsMatchInt, &arr[7]);
	TEST("TESTING Find", DLLIsEqualIter(iter, DLLEnd(dll)), 0); 

	DLLDestroy(dll);
}

static void TestMultiFind()
{
	int arr[] = {404, 11, 9001, 404, 69, 120, 404, 80085, 13, 99, 404};
	int arr_multi[] = {404, 404, 404, 404};

	size_t arr_size = sizeof(arr) / sizeof(int);
	size_t arr_size2 = sizeof(arr_multi) / sizeof(int);

	size_t i = 0;

	dllist_iter_t iter = NULL;

	dllist_t *dll = DLLCreate();
	dllist_t *multi_dll = DLLCreate();

	if(NULL == dll || NULL == multi_dll)
	{
		return;
	}

	iter = DLLBegin(dll);
	for(; i < arr_size; ++i)
	{
		iter = DLLPushFront(dll, &arr[i]);
		if(NULL == iter)
		{
			return;
		}
	}

	TEST("TESTING MultiFind", DLLMultiFind(DLLBegin(dll), DLLEnd(dll), IsMatchInt, &arr_multi[0], multi_dll), 4);
	TEST("TESTING MultiFind", DLLSize(multi_dll), arr_size2);

	iter = DLLBegin(multi_dll);

	for(i = 0; i < arr_size2; ++i, iter = DLLNext(iter))
	{
		TEST("TESTING MultiFind", *(int *)DLLGetData(iter), arr_multi[i]);
	}

	DLLDestroy(dll);
	DLLDestroy(multi_dll);
}

static void TestSplice()
{
	int arr[] = {15, 11, 9001, 12, 69, 120, 777, 80085, 13, 99, 404};
	int arr2[] = {400, 41, 43, 56};

	int arr_splice1[] = {15, 11, 80085, 13, 99, 404};
	int arr_splice2[] = {400, 9001, 12, 69, 120, 777, 41, 43, 56};

	int arr_splice3[] = {15, 11, 9001, 12, 69, 120, 777, 80085, 13, 99, 404, 400, 41, 43, 56};

	int arr_internal_splice[] = {400, 777, 41, 9001, 12, 69, 120, 43, 56};

	size_t arr_size = sizeof(arr) / sizeof(int);
	size_t arr_size2 = sizeof(arr2) / sizeof(int);

	size_t arr_splsize1 = sizeof(arr_splice1) / sizeof(int);
	size_t arr_splsize2 = sizeof(arr_splice2) / sizeof(int);

	size_t arr_splsize3 = sizeof(arr_splice3) / sizeof(int);

	size_t i = 0;

	dllist_iter_t iter = NULL;
	dllist_iter_t iter2 = NULL;
	dllist_iter_t iter3 = NULL;

	dllist_t *dll = DLLCreate();
	dllist_t *dll2 = DLLCreate();

	dllist_t *dll3 = DLLCreate();
	dllist_t *dll4 = DLLCreate();

	if(NULL == dll || NULL == dll2 || NULL == dll3 || NULL == dll4)
	{
		return;
	}

	/********** FILLINGS LISTS **********/

	iter = DLLBegin(dll);
	for(; i < arr_size; ++i)
	{
		iter = DLLPushBack(dll, &arr[i]);
		if(NULL == iter)
		{
			return;
		}
	}
	
	iter = DLLBegin(dll2);
	for(i = 0; i < arr_size2; ++i)
	{
		iter = DLLPushBack(dll2, &arr2[i]);
		if(NULL == iter)
		{
			return;
		}
	}
	
	iter = DLLBegin(dll3);
	for(i = 0; i < arr_size; ++i)
	{
		iter = DLLPushBack(dll3, &arr[i]);
		if(NULL == iter)
		{
			return;
		}
	}
	
	iter = DLLBegin(dll4);
	for(i = 0; i < arr_size2; ++i)
	{
		iter = DLLPushBack(dll4, &arr2[i]);
		if(NULL == iter)
		{
			return;
		}
	}

	/********** SPLICE TWO LISTS **********/

	iter = DLLNext(DLLBegin(dll));
	iter = DLLNext(iter);

	iter2 = DLLPrev(DLLEnd(dll));
	iter2 = DLLPrev(iter2);
	iter2 = DLLPrev(iter2);
	iter2 = DLLPrev(iter2);

	iter3 = DLLNext(DLLBegin(dll2));

	DLLSplice(iter, iter2, iter3);

	iter = DLLBegin(dll);
	for(i = 0; i < arr_splsize1; ++i, iter = DLLNext(iter))
	{
		TEST("TESTING Splice", *(int *)DLLGetData(iter), arr_splice1[i]);
	}

	iter = DLLBegin(dll2);
	for(i = 0; i < arr_splsize2; ++i, iter = DLLNext(iter))
	{
		TEST("TESTING Splice", *(int *)DLLGetData(iter), arr_splice2[i]);
	}


	/********** INTERNAL SPLICE **********/

	iter = DLLNext(DLLBegin(dll2));

	iter2 = DLLPrev(DLLEnd(dll2));
	iter2 = DLLPrev(iter2);
	iter2 = DLLPrev(iter2);
	iter2 = DLLPrev(iter2);

	iter3 = DLLPrev(DLLEnd(dll2));
	iter3 = DLLPrev(iter3);

	DLLSplice(iter, iter2, iter3);

	iter = DLLBegin(dll2);
	for(i = 0; i < arr_splsize2; ++i, iter = DLLNext(iter))
	{
		TEST("TESTING Splice", *(int *)DLLGetData(iter), arr_internal_splice[i]);
	}

	/********** HEAD TO HEAD SPLICE *********/
	
	iter = DLLBegin(dll3);

	iter2 = DLLEnd(dll3);

	iter3 = DLLBegin(dll4);

	DLLSplice(iter, iter2, iter3);

	iter = DLLBegin(dll4);
	for(i = 0; i < arr_splsize3; ++i, iter = DLLNext(iter))
	{
		TEST("TESTING Splice", *(int *)DLLGetData(iter), arr_splice3[i]);
	}

	TEST("TESTING Splice", DLLIsEmpty(dll3), 1);

	DLLDestroy(dll);
	DLLDestroy(dll2);
	DLLDestroy(dll3);
	DLLDestroy(dll4);

}

static int IsMatchInt(const void *data, void *param)
{
	if(NULL == data || NULL == param)
	{
		return 0;
	}
	
	return *(int *)data == *(int *)param;
}
