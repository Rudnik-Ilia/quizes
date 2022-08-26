#include<stdio.h>
#include<string.h>

#define LEN_STR 18
int main()
{

	int i;
	int j;
	char str[] = "I am ilia student!";
	
	
	for(i = LEN_STR; i > 0; )
	{	
		--i;	
		
		
		if(str[i] == ' ')
		{
			
			for(j = 0; j < LEN_STR - i -1 ; ++j)
			{
				printf("%c",str[i+j]);
			}
		}
	}










	
return 0;
}
