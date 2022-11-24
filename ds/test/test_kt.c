#include <stdio.h>
#include <stdlib.h>

#include "bitarray.h"
#include "kt.h"


int main ()
{
	size_t i = 0;
	size_t j = 0;
	int status = 0;
	
	pos_t pos = {6,6};
	
	
	int path[BOARD_MAX] = {0};
	
	status = KnightsTour(pos, path, 0, 200);
	
	if(status)
	{
		puts("IT'S NOT ENOUGH TIME. I CAN'T FINISH. BY-BY.");
	}
	puts(" ");
	
	for(i = 0, j = 1; i < BOARD_MAX; ++i, ++j)
	{
		printf("  %d ", path[i]);
		if(j == BOARD_SIDE)
		{
			printf("\n");
			j = 0;
			puts(" ");
		}
	}
	printf("\n");
	
    return (0);
}
