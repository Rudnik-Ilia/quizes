#include <stdio.h>

#include "kt.h"


/*
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
*/

int ARR[][SIZE] = {0}; 
int x_move[] = {2, 1, -1, -2, -2, -1, 1, 2};
int y_move[] = {1, 2, 2, 1, -1, -2, -2, -1};
/***************************************************************************************************************/
int KnightTour(int ARR[][SIZE], int i, int j, int step_count, int x_move[], int y_move[]);

static int IsValid(int i, int j, int ARR[SIZE][SIZE]);

void PrintMatrix();

int StartStep() ;
/***************************************************************************************************************/


static int IsValid(int i, int j, int ARR[][SIZE])
{
   return(i >= 1 && i <= SIZE && j >= 1 && j <= SIZE && ARR[i][j] == 0);
} 

int KnightTour(int ARR[][SIZE], int i, int j, int step_count, int x_move[], int y_move[]) 
{
	int k = 0;
	int next_i = 0;
	int next_j = 0;

	if (step_count == SIZE * SIZE)
	{
		return 1;
	}

	for(k = 0; k < SIZE; ++k) 
	{
		next_i = i + x_move[k];
		next_j = j + y_move[k];

		if(IsValid(i + x_move[k], j + y_move[k], ARR)) 
		{
			ARR[next_i][next_j] = step_count;

		if (KnightTour(ARR, next_i, next_j, step_count + 1, x_move, y_move))
		{
			return 1;
		}
			ARR[i + x_move[k]][j + y_move[k]] = 0; 
		}
	}
	return 0;
}  

int StartStep() 
{
	int i = 0;
	int j = 0;
	int x_move[] = {2, 1, -1, -2, -2, -1, 1, 2};
	int y_move[] = {1, 2, 2, 1, -1, -2, -2, -1};

	for(i = 1; i <= SIZE; i++) 
	{
		for(j = 1; j <= SIZE; j++) 
		{
			ARR[i][j] = 0;
		}
	}

	ARR[0][0] = 0; 

	if (KnightTour(ARR, 1, 1, 1, x_move, y_move)) 
	{
		for(i = 1; i <= SIZE; i++) 
		{
			for(j = 1; j <= SIZE; j++) 
			{
				printf("%d\t",ARR[i][j]);
			}

			printf("\n");
		}

		return 1;
	}
	ARR[0][0] = 1;
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
