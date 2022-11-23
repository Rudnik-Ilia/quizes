#include <stdio.h>
#include <stdlib.h>

#include "bitarray.h"
#include "kt.h"


int main ()
{
	size_t i = 0;
	int status = 0;
	pos_t pos = {3,1,0};
	
	
	int path[BOARD_MAX] = {0};
	
	status = KnightsTour(pos, path, 0, 20);
	if(status)
	{
		puts("IT'S NOT ENOUGH TIME. I CAN'T FINISH. BY-BY.");
	}
/*
	for(i = 0; i < BOARD_MAX; ++i)
	{
		printf("%d ", path[i]);
	
	}
*/	
    return (0);
}
