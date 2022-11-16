#include "heap.h"
#include "tests.h"
#include "util_v.h"

int CompareInt(const void *lhs, const void *rhs)
{
	VALIDATE(lhs, 2);
	return *(int*)lhs - *(int*)rhs;
}

int IsMatchInt(const void *data, const void *param)
{
	VALIDATE(data, 2);
	return *(int*)data == *(int*)param;
}

void Test1()
{
	heap_t *heap = NULL;
	int input[] = { 5, -1, 0, 4, 15, 10, 25, -10, 17 };
	int inserting_max[] = { 5, 5, 5, 5, 15, 15, 25, 25, 25 };
	int max_order[] = { 25, 17, 15, 10, 5, 4, 0, -1, -10 };
	size_t input_size = SIZEOF_ARR(input);
	size_t i = 0;

	if (NULL == (heap = HeapCreate(CompareInt)))
	{
		LOG_ERR(stderr, "Test1", "HeapCreate error");
		return;
	}
	TEST("Testing is empty", HeapIsEmpty(heap), 1);
	TEST("Testing size", HeapSize(heap), 0);

	/* Pushing */
	for (i = 0; i < input_size; ++i)
	{
		if (0 != HeapPush(heap, input + i))
		{
			LOG_ERR(stderr, "Test1", "HeapPush");
			HeapDestroy(heap);
			return;
		}
		TEST("Testing peek", *(int*)HeapPeek(heap), inserting_max[i]);
		TEST("Testing size", HeapSize(heap), i + 1);
	}
	TEST("Testing is empty", HeapIsEmpty(heap), 0);

	/* Testing peek pop */
	for (i = 0; !HeapIsEmpty(heap); ++i)
	{
		TEST("Testing peek", *(int*)HeapPeek(heap), max_order[i]);
		HeapPop(heap);
	}

	/* Pushing */
	for (i = 0; i < input_size; ++i)
	{
		if (0 != HeapPush(heap, input + i))
		{
			LOG_ERR(stderr, "Test1", "HeapPush");
			HeapDestroy(heap);
			return;
		}
	}

	/* Testing peek remove */
	for (i = 0; !HeapIsEmpty(heap); ++i)
	{
		TEST("Testing peek", *(int*)HeapPeek(heap), max_order[i]);
		HeapRemove(heap,IsMatchInt, max_order + i);
	}


	HeapDestroy(heap);
}

void Test2()
{
	heap_t *heap = NULL;
	int input[] = { 6, 10, 10, 6, 11, 15, 23, 20, 42, 43, 6, 6 };
	int inserting_max[] = { 6, 10, 10, 10, 11, 15, 23, 23, 42, 43, 43, 43 };
	int max_order[] = { 43, 42, 23, 20, 15, 11, 10, 10, 6, 6, 6, 6 };
	size_t input_size = SIZEOF_ARR(input);
	size_t i = 0;

	if (NULL == (heap = HeapCreate(CompareInt)))
	{
		LOG_ERR(stderr, "Test1", "HeapCreate error");
		return;
	}

	/* Pushing */
	for (i = 0; i < input_size; ++i)
	{
		if (0 != HeapPush(heap, input + i))
		{
			LOG_ERR(stderr, "Test1", "HeapPush");
			HeapDestroy(heap);
			return;
		}
		TEST("Testing peek", *(int*)HeapPeek(heap), inserting_max[i]);
	}

	/* Testing peek pop */
	for (i = 0; !HeapIsEmpty(heap); ++i)
	{
		TEST("Testing peek", *(int*)HeapPeek(heap), max_order[i]);
		HeapPop(heap);
	}

	/* Pushing */
	for (i = 0; i < input_size; ++i)
	{
		if (0 != HeapPush(heap, input + i))
		{
			LOG_ERR(stderr, "Test1", "HeapPush");
			HeapDestroy(heap);
			return;
		}
	}

	/* Testing peek remove */
	for (i = 0; !HeapIsEmpty(heap); ++i)
	{
		TEST("Testing peek", *(int*)HeapPeek(heap), max_order[i]);
		HeapRemove(heap,IsMatchInt, max_order + i);
	}

	HeapDestroy(heap);
}

void Test3()
{
	heap_t *heap = NULL;
	int input[] = { 6, 10, 10, 6, 11, 15, 23, 20, 42, 43, 6, 6 };
	int max_order[] = { 43, 42, 23, 11, 10, 6, 6, 6 };
	int to_remove[] = { 20, 6, 10, 15 };
	size_t input_size = SIZEOF_ARR(input);
	size_t remove_size = SIZEOF_ARR(to_remove);
	size_t i = 0;

	if (NULL == (heap = HeapCreate(CompareInt)))
	{
		LOG_ERR(stderr, "Test1", "HeapCreate error");
		return;
	}

	/* Pushing */
	for (i = 0; i < input_size; ++i)
	{
		if (0 != HeapPush(heap, input + i))
		{
			LOG_ERR(stderr, "Test1", "HeapPush");
			HeapDestroy(heap);
			return;
		}
	}

	/* Random removing */
	for (i = 0; i < remove_size; ++i)
	{
		HeapRemove(heap, IsMatchInt, to_remove + i);
	}

	/* Testing peek pop */
	for (i = 0; !HeapIsEmpty(heap); ++i)
	{
		TEST("Testing peek", *(int*)HeapPeek(heap), max_order[i]);
		HeapPop(heap);
	}

	HeapDestroy(heap);
}

int main()
{
	Test1();
	Test2();
	Test3();
	PASS;
	return 0;
}
