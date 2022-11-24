
#include <stdio.h>
#include <stdlib.h>/*calloc*/
#include <time.h> /*time*/

#include "kt.h"
#include "bitarray.h"

#define WORD (64)


/******************************************************************************************************************/
static int KnightTourHer(int x, int y, int *buf, unsigned long board, time_t limit);
static int KnightTourNoHer(int x, int y, int *buf, unsigned long board, time_t limit);
static void PrintArr(int *arr);
static int CmpFunc(const void *data1, const void *data2);
static size_t IndexInArray(int x, int y);
static int IsValidOption(int x, int y, unsigned long board);
static int CountOptions(pos_t pos, unsigned long board);
static size_t CountOn(unsigned long bit_array);
static int BitIsOn(unsigned long bit_arr, unsigned int bit_num);
static unsigned long BitSetOn(unsigned long bit_arr, unsigned int bit_num);
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
	
    	time_t limit = !!timeout * (time(NULL) + timeout);
    	
	int *tmp = (int *)calloc(BOARD_MAX * 2, sizeof(int));
	
	if(heuristic_on)
	{
		status = KnightTourNoHer(x, y, tmp, 0u, limit);
	}
	else
	{	
		status = KnightTourHer(x, y, tmp, 0u, limit);
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

int KnightTourHer(int x, int y, int *buf, unsigned long board, time_t limit)
{	
	if (0 != limit && time(NULL) >= limit)
	{
		return 1;
	}
	if (!IsValidOption(x, y, board))
	{
		return 1;
	}

	board = BitSetOn(board, IndexInArray(x, y));

	*buf = x;

	*(buf + 1) = y;
	

	if (CountOn(-1lu<<(WORD - BOARD_MAX)) == CountOn(board))
	{
		return 0;
	}
	
	if (KnightTourHer(x + 2, y + 1, buf + 2, board, limit) == 0)
	{
		return 0;
	}
	if (KnightTourHer(x + 1, y + 2, buf + 2, board, limit) == 0)
	{
		return 0;
	}
	if (KnightTourHer(x - 1, y + 2, buf + 2, board, limit) == 0)
	{
		return 0;
	}
	if (KnightTourHer(x - 2, y + 1, buf + 2, board, limit) == 0)
	{
		return 0;
	}
	if (KnightTourHer(x - 2, y - 1, buf + 2, board, limit) == 0)
	{
		return 0;
	}
	if (KnightTourHer(x - 1, y - 2, buf + 2, board, limit) == 0)
	{
		return 0;
	}
	if (KnightTourHer(x + 1, y - 2, buf + 2, board, limit) == 0)
	{
		return 0;
	}
	if (KnightTourHer(x + 2, y - 1, buf + 2, board, limit) == 0)
	{
		return 0;
	}
	return 1;
}



int KnightTourNoHer(int x, int y, int *buf, unsigned long board, time_t limit)
{
	pos_t steps_arr[8];
	size_t i = 0;
	
	if (0 != limit && time(NULL) >= limit)
	{
		return 1;
	}
	
	if (!IsValidOption(x, y, board))
	{
		return 1;
	}

	board = BitSetOn(board, IndexInArray(x, y));

	*buf = x;

	*(buf + 1) = y;

	if(CountOn(-1lu<<(WORD - BOARD_MAX)) == CountOn(board))
	{
		return 0;
	}
	steps_arr[0].x = x - 2;
	steps_arr[0].y = y + 1;
	steps_arr[1].x = x - 1;
	steps_arr[1].y = y + 2;
	steps_arr[2].x = x + 1;
	steps_arr[2].y = y + 2;
	steps_arr[3].x = x + 2;
	steps_arr[3].y = y + 1;
	steps_arr[4].x = x + 2;
	steps_arr[4].y = y - 1;
	steps_arr[5].x = x + 1;
	steps_arr[5].y = y - 2;
	steps_arr[6].x = x - 1;
	steps_arr[6].y = y - 2;
	steps_arr[7].x = x - 2;
	steps_arr[7].y = y - 1;

	for (i = 0; i < 8; ++i)
	{
		steps_arr[i].steps = CountOptions(steps_arr[i], board);
	}

	qsort(steps_arr, 8, sizeof(pos_t), CmpFunc);

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


static int CountOptions(pos_t pos, unsigned long board)
{
	int x = pos.x;
	int y = pos.y;

	if (!IsValidOption(x, y, board))
	{
		return (-1);
	}

	return (IsValidOption(x - 2, y + 1, board) + IsValidOption(x - 1, y + 2, board) +
	    	IsValidOption(x + 1, y + 2, board) + IsValidOption(x + 2, y + 1, board) +
	    	IsValidOption(x + 2, y - 1, board) + IsValidOption(x + 1, y - 2, board) +
	    	IsValidOption(x - 1, y - 2, board) + IsValidOption(x - 2, y - 1, board));
}

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

static size_t IndexInArray(int x, int y)
{
    	return (x * BOARD_SIDE + y + 1);
}

static int IsValidOption(int x, int y, unsigned long board)
{
    	return (!((x < 0) || (x > BOARD_SIDE - 1) || (y < 0) || (y > BOARD_SIDE - 1) || (BitIsOn(board, IndexInArray(x, y)))));
}

static int CmpFunc(const void *data1, const void *data2)
{
    	return (((pos_t*)data1)->steps - ((pos_t*)data2)->steps);
}
/**************************************************************************/
static size_t CountOn(unsigned long bit_array)
{
	size_t temp = 0;
	
	while(bit_array)
	{
		temp+=bit_array & 1;
		bit_array = bit_array >> 1;
	}
	return temp;
}
static int BitIsOn(unsigned long bit_arr, unsigned int bit_num)
{
    	return ((bit_arr >> (bit_num-1)) & 1);
}
static unsigned long BitSetOn(unsigned long bit_arr, unsigned int bit_num)
{
    	return (bit_arr | (1ul << (bit_num-1)));
}
/****************************************************************************/



