#include <stdio.h>
#include "kt.h"


int ARR[][8] = {
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
};

int x_move[] = {2, 1, -1, -2, -2, -1, 1, 2};

int y_move[] = {1, 2, 2, 1, -1, -2, -2, -1};

int Valid(int x,int y)
{
	return !(x >=0 && y>=0 && x < 7 && y < 7 && ARR[x][y] == -1);
}
int Step(int x, int y, int st)
{	
	size_t i = 0;
	int step = st;
	int move_x = x;
	int move_y = y;
	
	if(step == 64)
	{
		return 1;
	}
	for(i = 0; i < 8; ++i)
	{
		move_x = x + x_move[i];
		move_y = y + y_move[i];
		if(Valid(move_x, move_y))
		{
			ARR[move_x][move_y] = (step += 1);
			if(Step(x, y, step + 1) == 1)
			{
				return 1;
			}
			else
			{
				ARR[move_x][move_y] = (step -= 1);
			}
		}
	}
	return 0;
	
}





























/******************************************************************************************/
void ShowMat()
{	
	size_t i = 0;
	size_t j = 0;
	for(i = 0; i < 8; ++i)
	{
		for(j = 0; j < 8; ++j)
		{
			printf("%d ", ARR[i][j]);
		}
	printf("\n");
	}
	printf("\n");
}
