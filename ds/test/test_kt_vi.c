#include <stdio.h>
#include <time.h> /* time_t */


#include "tests_vi.h"
#include "kt.h"

size_t test_counter = 0;
size_t success_counter = 0;


void Tests();
void PrintArr(int *arr);

int main()
{
	Tests();	
	
	SHOWRESULTS;

	return 0;
}

void Tests()
{
	int path[BOARD_MAX];
	pos_t pos = {0,0, 0};
	time_t time = 100;
	
	TEST(0, KnightsTour(pos, path, 1, time));
	TEST(0, KnightsTour(pos, path, 0, time));
}

void PrintArr(int *arr)
{
	size_t i = 0;
	size_t j = 0;
	for( ;i<BOARD_SIDE; ++i)
	{
		for(j=0 ;j<BOARD_SIDE; ++j)
		{
			printf("%d   ", arr[i*BOARD_SIDE+j]);
		}
		puts(" ");
	}
}

