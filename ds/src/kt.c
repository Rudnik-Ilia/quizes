
#include <stdio.h>
#include <stdlib.h>/*calloc*/
#include <time.h> /*time*/
#include <assert.h>
#include "kt.h"
#include "bitarray.h"

#define WORD (64)

typedef struct
{
	int x;
	int y;
	int steps;
}help_t;

static int X[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
static int Y[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

/******************************************************************************************************************/
static int KnightTourHer(int x, int y, int *buf, size_t board, time_t limit);
static int KnightTourNoHer(int x, int y, int *buf, size_t board, time_t limit);
static int CmpFunc(const void *data1, const void *data2);
static size_t IndexInArray(int x, int y);
static int IsValidOption(int x, int y, size_t board);
static int CountOptions(help_t pos, size_t board);
static int BitIsOn(size_t bit_arr, unsigned int bit_num);
/******************************************************************************************************************/

int KnightsTour(pos_t pos, int path[BOARD_MAX], int heuristic_on, time_t timeout)
{
	int x = pos.x;
    	int y = pos.y;
    	int step = 0;
	int i = 0;
	size_t j = 0;
	size_t k = 0;
	int status = 0;
	int arr[BOARD_SIDE][BOARD_SIDE] = {0};
    	time_t limit =  0;
	
 	int *tmp = (int *)calloc(BOARD_MAX * 2, sizeof(int));
	assert(NULL != path);	
	
    	limit = !!timeout * (time(NULL) + timeout);
    	
	if(heuristic_on)
	{
		status = KnightTourNoHer(x, y, tmp, 0, limit);
	}
	else
	{	
		status = KnightTourHer(x, y, tmp, 0, limit);
	}
	
	for (i = 0; i < BOARD_MAX * 2; i += 2)
	{
		arr[tmp[i]][tmp[i + 1]] = (step += 1);
	}

	for(i = 0; i < BOARD_SIDE ; ++i)
	{
		for(j = 0; j < BOARD_SIDE ; ++j, ++k)
		{
			path[k] = arr[i][j];
		}
	
	}

	free(tmp);
	return status;

}

int KnightTourHer(int x, int y, int *buf, size_t board, time_t limit)
{	
	size_t i = 0;
	assert(NULL != buf);	
	
	if (0 != limit && time(NULL) >= limit)
	{
		return 1;
	}
	if (!IsValidOption(x, y, board))
	{
		return 1;
	}

	board = BitArraySetOn(board, IndexInArray(x, y));

	*buf = x;
	*(buf + 1) = y;
	
	if (BOARD_MAX == BitArrayCountOn(board))
	{
		return 0;
	}
	
	for(i = 0; i < 8; ++i)
	{
		if (KnightTourHer(x + X[i], y + Y[i], buf + 2, board, limit) == 0)
		{
			return 0;
		}
	}
	return 1;
}



int KnightTourNoHer(int x, int y, int *buf, size_t board, time_t limit)
{	
	help_t steps_arr[8];
	size_t i = 0;
	
	assert(NULL != buf);
	
	if (0 != limit && time(NULL) >= limit)
	{
		return 1;
	}
	
	if (!IsValidOption(x, y, board))
	{
		return 1;
	}

	board = BitArraySetOn(board, IndexInArray(x, y));

	*buf = x;
	*(buf + 1) = y;

	if(BOARD_MAX == BitArrayCountOn(board))
	{
		return 0;
	}
	
	for(i = 0; i < 8; ++i)
	{
		steps_arr[i].x = x - X[i];
		steps_arr[i].y = y + Y[i];
	}

	for (i = 0; i < 8; ++i)
	{
		steps_arr[i].steps = CountOptions(steps_arr[i], board);
	}
	
	qsort(steps_arr, 8, sizeof(help_t), CmpFunc);

	for (i = 0; i < 8; ++i)
	{
		if (steps_arr[i].steps > -1)
		{
		    if (!KnightTourNoHer(steps_arr[i].x, steps_arr[i].y, buf + 2, board, limit))
		    {
			return 0;
		    }
		}
	}
	return 1;
}

static int CountOptions(help_t pos, size_t board)
{
	int x = pos.x;
	int y = pos.y;
	size_t i = 0;
	int degree = 0;

	if (!IsValidOption(x, y, board))
	{
		return -1;
	}

	for(i = 0; i < 8; ++i)
	{
		degree += IsValidOption(x - X[i], y + Y[i], board);
	}
	return degree;
	
}
static size_t IndexInArray(int x, int y)
{
    	return (x * BOARD_SIDE + y + 1);
}

static int IsValidOption(int x, int y, size_t board)
{
    	return (!((x < 0) || (x > BOARD_SIDE - 1) || (y < 0) || (y > BOARD_SIDE - 1) || (BitIsOn(board, IndexInArray(x, y)))));
}

static int CmpFunc(const void *data1, const void *data2)
{
	assert(NULL != data1);
	assert(NULL != data2);
	
    	return (((help_t*)data1)->steps - ((help_t*)data2)->steps);
}
/**************************************************************************/
static int BitIsOn(size_t bit_arr, unsigned int bit_num)
{
    	return ((bit_arr >> (bit_num-1)) & 1);
}
/****************************************************************************/
/*
void PrintArr(int *arr)
{
	size_t i = 0;
	size_t j = 0;
	for( ; i < BOARD_SIDE; ++i)
	{
		for(j = 0 ;j < BOARD_SIDE; ++j)
		{
			printf("%d   ", arr[i * BOARD_SIDE + j]);
		}
		puts(" ");
	}
}
*/



