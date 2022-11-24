/****************************
*Author: Roni Zemelman
*Group: OL132              
*WS: Knight Tour
*Date: 22/11/2022                   
*Reviewer: Ilia         
*Status: -          
****************************/

#include <stdio.h> /* printf for debugging */
#include <stdlib.h> /* qsort */

#include "bitarray.h"
#include "kt.h"

#define NUM_POSSIBLE_MOVES 8

#define TRUE 1
#define FALSE 0

#define XY_TO_NUM(pos) (((pos).y * BOARD_SIDE) + (pos).x)

#define UNUSED(x) (void) x

#define IS_VISITED(bit_array, pos) (TRUE == BitArrayGetBit(visited, XY_TO_NUM(pos)))
#define INDEX_IS_LEGAL(index) (index < BOARD_SIDE && index >= 0)
#define ISVALID(pos) ((INDEX_IS_LEGAL(pos.x) && (INDEX_IS_LEGAL(pos.y)) &&  !IS_VISITED(bit_array, pos)))

#define MOVE_IS_LEGAL(i) ((INDEX_IS_LEGAL(next.x + AddX[i]) && INDEX_IS_LEGAL(next.y + AddY[i])))

#define INIT_NEIGHBORS(pos, neighbors)   		neighbors[0].x = pos.x + 2;  \
												neighbors[0].y = pos.y + 1;  \
												neighbors[1].x = pos.x + 1;  \
												neighbors[1].y = pos.y + 2; \
												neighbors[2].x = pos.x - 1; \
												neighbors[2].y = pos.y + 2; \
												neighbors[3].x = pos.x - 2; \
												neighbors[3].y = pos.y + 1; \
												neighbors[4].x = pos.x - 2; \
												neighbors[4].y = pos.y - 1; \
												neighbors[5].x = pos.x - 1; \
												neighbors[5].y = pos.y - 2; \
												neighbors[6].x = pos.x + 1; \
												neighbors[6].y = pos.y - 2; \
												neighbors[7].x = pos.x + 2; \
												neighbors[7].y = pos.y - 1; \

#define INIT_UNIS_VISITED_NEIGHBORS(pos, neighbors) INIT_NEIGHBORS(pos, neighbors); \
												for (i = 0; i < NUM_POSSIBLE_MOVES; ++i) \
													neighbors[i].x = (neighbors[i].x * (IS_VISITED(bit_array, neighbors[i]) * -1)); \
												 
#define GOAL_REACHED(bit_array)  ((BOARD_SIDE * BOARD_SIDE) == BitArrayCountOn(bit_array))

#define MARK_VISITED(pos)   (visited = BitArraySetOn(visited, XY_TO_NUM(pos)))
#define UNMARK_VISITED(pos) (visited = BitArraySetOff(visited, XY_TO_NUM(pos)))	

#define GET_DEADLINE(timeout) (!!timeout * (time(NULL) + timeout))
#define TIME_EXPIRED(deadline) (deadline && time(NULL) >= deadline)


static int AddX[NUM_POSSIBLE_MOVES] = { 2, 1, -1, -2, -2, -1, 1, 2 };
static int AddY[NUM_POSSIBLE_MOVES] = { 1, 2, 2, 1, -1, -2, -2, -1 };

static int GetDegree(pos_t next)
{
	int i = 0;
	int count = 0;

	for (i = 0; i < NUM_POSSIBLE_MOVES; ++i)
	{
		count += MOVE_IS_LEGAL(i); 
	}
	
	return count;
}

static int CompareDegree(const void *pos1, const void *pos2)
{
	pos_t *position1 = (pos_t *) pos1;
	pos_t *position2 = (pos_t *) pos2;
	
	return GetDegree(*position1) - GetDegree(*position2);
}
						
static int RecurseTour(pos_t pos, int step, int path[BOARD_MAX], bit_array_t visited, int heuristic_on, time_t deadline)
{
	pos_t neighbors[NUM_POSSIBLE_MOVES] = {0};
	int result = FALSE;
	int i = 0;
	
	MARK_VISITED(pos);
	path[XY_TO_NUM(pos)] = step;
	
	if (TIME_EXPIRED(deadline))
		return FALSE;
		
	if (GOAL_REACHED(visited))
		return TRUE;
	
	INIT_NEIGHBORS(pos, neighbors);
	
	if (heuristic_on)
		qsort(neighbors, NUM_POSSIBLE_MOVES, sizeof(pos_t), CompareDegree);
	
	for (i = 0; i < NUM_POSSIBLE_MOVES; ++i)
	{
		if (!ISVALID(neighbors[i]))
			continue;
		
		result = RecurseTour(neighbors[i], step + 1,  path, visited, heuristic_on, deadline);
		
		if (TRUE == result)
			return TRUE;
		
		UNMARK_VISITED(neighbors[i]); 
	}
	
	return FALSE;
}

int KnightsTour(pos_t pos, int path[BOARD_MAX], int heuristic_on, time_t timeout)
{
	bit_array_t visited = 0;
	
	time_t deadline = GET_DEADLINE(timeout);
	
	return RecurseTour(pos, 0, path, visited, heuristic_on, deadline);
}
