#include <stdlib.h>

#include "avl.h"
#include "test_jo.h"

int CmpInt(const void *data, const void *data_key);
int Cmp_Func(const void *data1, const void *data2);
int ForEach_Test(void *data, void *param);
static void TestGeneral();
static void Test2();

typedef struct param_data
{
    char data[10];
    size_t counter;
}param_data_t;

typedef struct data_pack
{
    void *data;
    size_t key;
}data_pack_t;

int main()
{
    TestGeneral();

    Test2();

    EXPRESSIVE_PASS;

    return 0;
}

static void TestGeneral()
{
    size_t i = 0;

    avl_t *avl = NULL;

    char data[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    param_data_t preorder_param = {{'A', 'B', 'C', 'D', 'H', 'E', 'F', 'G', 'I', 'J'}, 0};
    param_data_t inorder_param = {{'C', 'B', 'H', 'D', 'A', 'F', 'E', 'I', 'G', 'J'}, 0};
    param_data_t postorder_param = {{'C', 'H', 'D', 'B', 'F', 'I', 'J', 'G', 'E',  'A'}, 0};

    size_t keys[10] = {5, 2, 1, 4, 7, 6, 9, 3, 8, 10};
    size_t height_map[10] = {1, 2, 2, 3, 3, 3, 3, 4, 4, 4};

    data_pack_t data_packs[10];

    char data_dummy = 'P';
    data_pack_t data_pack_dummy;

    data_pack_dummy.data = &data_dummy;
    data_pack_dummy.key = 999;

    for(;i < 10; ++i)
    {
        data_packs[i].data = &data[i];
        data_packs[i].key = keys[i];
    }

    avl = AVLCreate(Cmp_Func);

    TEST("Testing AVLCreate", NULL != avl, 1);
    if(NULL == avl)
    {
        FAILED;
        return;
    }

    TEST("Testing AVLIsEmpty after AVLCreate", AVLIsEmpty(avl), 1);
    TEST("Testing AVLHeight after AVLCreate", AVLHeight(avl), 0);
    TEST("Testing AVLSize after AVLCreate", AVLSize(avl), 0);

    for(i = 0; i < 10; ++i)
    {
        TEST("Testing AVLInsert", AVLInsert(avl, &data_packs[i]), 0);
        TEST("Testing AVLHeight while AVLInsert", AVLHeight(avl), height_map[i]);
        TEST("Testing AVLIsEmpty while AVLInsert", AVLIsEmpty(avl), 0);
        TEST("Testing AVLSize while AVLInsert", AVLSize(avl), i + 1);
    }

    inorder_param.data[4] = 'X';

    TEST("Tesing AVLForEach Preorder", AVLForEach(avl, ForEach_Test, &preorder_param, PRE_ORDER), 0);
    TEST("Tesing AVLForEach InOrder", AVLForEach(avl, ForEach_Test, &inorder_param, IN_ORDER), 1);
    TEST("Tesing AVLForEach PostOrder", AVLForEach(avl, ForEach_Test, &postorder_param, POST_ORDER), 0);

    preorder_param.data[4] = 'X';
    preorder_param.counter = 0;

    inorder_param.data[4] = 'A';
    inorder_param.counter = 0;

    postorder_param.data[4] = 'X';
    postorder_param.counter = 0;

    TEST("Tesing AVLForEach Preorder", AVLForEach(avl, ForEach_Test, &preorder_param, PRE_ORDER), 1);
    TEST("Tesing AVLForEach InOrder", AVLForEach(avl, ForEach_Test, &inorder_param, IN_ORDER), 0);
    TEST("Tesing AVLForEach PostOrder", AVLForEach(avl, ForEach_Test, &postorder_param, POST_ORDER), 1);

    for(i = 0; i < 10; ++i)
    {
        TEST("Tesitng AVLFind", *(char *)(*(data_pack_t *)AVLFind(avl, &data_packs[i])).data, data[i]);
    }

    TEST("Tesitng AVLFind", NULL == AVLFind(avl, &data_pack_dummy), 1);

    TEST("Testing AVLIsEmpty after AVLInsert", AVLIsEmpty(avl), 0);

    AVLRemove(avl, &data_packs[4]);
    TEST("Testing AVLSize while AVLRemove", AVLSize(avl), 9);
    TEST("Testing AVLHeight while AVLInsert", AVLHeight(avl), 4);

    AVLRemove(avl, &data_packs[1]);
    TEST("Testing AVLSize while AVLRemove", AVLSize(avl), 8);
    TEST("Testing AVLHeight while AVLInsert", AVLHeight(avl), 4);

    AVLRemove(avl, &data_packs[9]);
    TEST("Testing AVLSize while AVLRemove", AVLSize(avl), 7);
    TEST("Testing AVLHeight while AVLInsert", AVLHeight(avl), 3);

    AVLRemove(avl, &data_packs[5]);
    TEST("Testing AVLSize while AVLRemove", AVLSize(avl), 6);
    TEST("Testing AVLHeight while AVLInsert", AVLHeight(avl), 3);

    AVLRemove(avl, &data_packs[8]);
    TEST("Testing AVLSize while AVLRemove", AVLSize(avl), 5);
    TEST("Testing AVLHeight while AVLInsert", AVLHeight(avl), 3);

    AVLRemove(avl, &data_packs[6]);
    TEST("Testing AVLSize while AVLRemove", AVLSize(avl), 4);
    TEST("Testing AVLHeight while AVLInsert", AVLHeight(avl), 3);

    AVLRemove(avl, &data_packs[2]);
    TEST("Testing AVLSize while AVLRemove", AVLSize(avl), 3);
    TEST("Testing AVLHeight while AVLInsert", AVLHeight(avl), 2);

    AVLDestroy(avl);
}

/*TEST 2  generously donated by Vadim*/

#define FACTOR 1.44

#define TREE_HEIGHT_BY_SIZE(size) \
	((log((size) + 1) / log(2)) * FACTOR)

#define INPUT_SIZE 2000
int IsValInArr(int *arr, size_t size, int val)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		if (val == arr[i])
		{
			return 1;
		}
	}
	return 0;
}

int GetUniqueRandInt(size_t min, size_t max)
{
	static int buff[INPUT_SIZE] = { 0 };
	static size_t offset = 0;
	int r = 0;

	for (r = min + rand() % (max + 1 - min);
		0 != IsValInArr(buff, INPUT_SIZE, r);
		r = min + rand() % (max + 1 - min))
	{
		/* Empty body */
	}
	buff[offset++] = r;
	return r;
}

void Test2()
{
	int input[INPUT_SIZE];
	size_t i = 0;
	avl_t *tree = NULL;

	/* fill up input array */
	for (i = 0; i < INPUT_SIZE; ++i)
	{
		int sign = -1;
		int rf = rand() % 2;
		input[i] = GetUniqueRandInt(0, 100000);
		sign += rf + rf;
		input[i] *= sign;
	}

	tree = AVLCreate(CmpInt);
	if (NULL == tree)
	{
		return;
	}


	for (i = 0; i < INPUT_SIZE; ++i)
	{
		if (0 != AVLInsert(tree, &(input[i])))
		{
			AVLDestroy(tree);
			return;
		}
		TEST("Testing size", AVLSize(tree), i + 1);
		TEST("Testing balance", AVLHeight(tree) <= (size_t)TREE_HEIGHT_BY_SIZE(i + 1), 1);
	}

	for (i = 0; i < INPUT_SIZE; ++i)
	{
		AVLRemove(tree, &(input[i]));

		TEST("Testing size", AVLSize(tree), INPUT_SIZE - i - 1);
		if (!AVLIsEmpty(tree))
		{
			TEST("Testing balance",
				AVLHeight(tree) <= (size_t)TREE_HEIGHT_BY_SIZE(INPUT_SIZE - i - 1), 1);
		}
	}

	AVLDestroy(tree);
}

/************************************************************************************************/

int CmpInt(const void *data, const void *data_key)
{
	return *((int*)data) - *((int*)data_key);
}


int Cmp_Func(const void *data1, const void *data2)
{
    return (*(data_pack_t *)data1).key - (*(data_pack_t *)data2).key;
}

int ForEach_Test(void *data, void *param)
{
    size_t counter = (((param_data_t *)param)->counter)++;

    char c_param = ((param_data_t *)param)->data[counter];
    char c_node = (*(char*)(*(data_pack_t *)data).data);
    /*
    printf("counter:%lu\n", counter);
    printf("Comparing: %c with %c\n",c_node, c_param);
    printf("Cmp res:%d\n", !(c_node == c_param));
    */
    return !(c_node == c_param);
}
