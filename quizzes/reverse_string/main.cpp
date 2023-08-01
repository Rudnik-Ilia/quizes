#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>


#define LEN_STR 19
#define LEN_REVERSE 22

int main()
{

	int count = 0;
	int record = 0;
	char str[] = " I am ilia student!";
	char* second = (char*)malloc(LEN_REVERSE);
	
	for(int i = LEN_STR ; i > 0;--i )
	{	
		--i;	
		if(str[i] == ' ')
		{	
			--count;
			for(int j = 0; j < LEN_STR - count; ++j)
			{		
				second[record++] = str[i+j];
				++count;
			}
		}
	}
	

	std::cout << second << std::endl;

    return 0;
}
