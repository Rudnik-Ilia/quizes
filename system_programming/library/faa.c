#include <stdio.h>
#include <stdlib.h>


void Faa(int x)
{
	void * ptr = NULL;
	int a = 0;
	static int b = 1;
	static const int c = 2;
	char d = 'd';
	char arr[] = "ilia";
	ptr = (void *)malloc(100);
	
	printf("%d\n", x+100);
}
