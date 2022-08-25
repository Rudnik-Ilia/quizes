#include <stdlib.h> /*free*/
#include <string.h> /* strlen */
#include<stdio.h>/* printf */


#include"ws8_5.h"

int Writer(student * st)
{
	
	FILE *file;
	file = fopen("data.dat", "wb");
	if(NULL == file)
	{
		puts("No memory for you!Sorry!");
	}
	fwrite(st, sizeof(student), 1, file);
	fclose(file);
	return 0;
}

int Reader(student * st)
{
	FILE *file;
	file = fopen("data.dat", "rb");
	if(NULL == file)
	{
		puts("No memory for you!Sorry!");
	}
	fread(st, sizeof(student), 1, file);
	fclose(file);
	return 0;
}


