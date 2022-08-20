
#include <stdio.h>/*printf*/

size_t CountSetBits_Loop(unsigned int x)
{
	int byte;
	size_t count;
	count = 0;
	byte = 32;
	while(--byte)
	{
		count = count + ((x) & 1);
		x = x >> 1;
	}
	return count;

}

void CreaterLut()
{ 
	
	unsigned int  i;
	FILE* f = fopen("LUTtable.txt", "w");
	for(i = 0; i < 20; ++i)
	{
		fprintf( f,"%lu", CountSetBits_Loop(i));
	}
	
	
		
	fclose(f);
}


int main()
{


	CreaterLut();




return 0;
}


