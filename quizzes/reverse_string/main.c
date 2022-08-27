#include<stdio.h>
#include<string.h>
#include <stdlib.h>


#define LEN_STR 19
#define LEN_REVERSE 22
int main()
{

	int i;
	int j;
	int count;
	int record;
	char str[] = " I am ilia student!";
	char* second = (char*)malloc(LEN_REVERSE);
	count = 0;
	record = 0;
	
	
	for(i = LEN_STR ; i > 0; )
	{	
		--i;	
		if(str[i] == ' ' || i == 0)
		{	
			count-=1;
			for(j = 0; j < LEN_STR - count; ++j)
			{
				/*
				*/
				printf("%c\n",str[i+j]);
				
				second[record++] = str[i+j];
				
	
				++count;
			}
		}
	}
	
	for(i = 0; i < LEN_REVERSE ; ++i)
	{
		printf("%c", second[i]);
	}









	
return 0;
}
