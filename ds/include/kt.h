#ifndef __KT_H__
#define __KT_H__

#include <time.h>

#ifndef BOARD_SIDE
#define BOARD_SIDE (8)
#endif /* BOARD_SIDE */

#define BOARD_MAX BOARD_SIDE * BOARD_SIDE

typedef struct pos
{
	int x;
	int y;
}pos_t;

/*
* @brief: Tries to run a knights tour on a nxn board, from a given position. 
* @params:	@pos - Starting position of knight
		@path - outparam, contains the complete path taken by the knight
		@heuristic_on - boolean to toggle heuristic approach
		@timeout - a timeout interval, in seconds, for how long the path may be calculated.
			   set it to 0 seconds for no timeout.
* @return: returns a boolean describing the success of the knights tour
			@TRUE - a knights tour was possible
			@FALSE - a knights tour was not possible
* @complexity: O(8^(nÂ²))
*/
int KnightsTour(pos_t pos, int path[BOARD_MAX], int heuristic_on, time_t timeout);


#endif /* __KTR_H__*/
