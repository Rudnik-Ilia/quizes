#ifndef __KT_H__
#define __KT_H__

#ifndef BOARD_MAX
#define BOARD_MAX 64
#endif /* BOARD_MAX */

typedef struct pos
{
	unsigned int x;
	unsigned int y;
}pos_t;

/*
* @brief: Tries to run a knights tour on a nxn board, from a given position. 
* @params:	@pos - Starting position of knight
		@path - outparam, contains the complete path taken by the knight
		@heuristic_on - boolean to toggle heuristic approach
* @return: returns a boolean describing the success of the knights tour
			@TRUE - a knights tour was possible
			@FALSE - a knights tour was not possible
* @complexity: O(8^(n²))
*/
int KnightsTour(pos_t pos, int path[BOARD_MAX], int heuristic_on);

void ShowMat();
int Step(int x, int y, int step);

#endif /* __KTR_H__*/
