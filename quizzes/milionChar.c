#include <stdio.h>

#include <string.h>



/*
void milion(char x)
{
	static char arr[256];
	static size_t tmp;
	int flag = 1;
	if(flag)
	{
		memset(arr, 0, 256);
		flag = 0;
		tmp = 0;
	}
	if('0' != x)
	{
		++arr[x];
		if(arr[x] > tmp)
		{
		printf("%ld",arr[x]);
		
			tmp = arr[x];
		}	
	}
	else
	{
		printf("%ld", tmp);
		flag = 1;		
	}
}
		
*/
void milion(char x)
{
	static char arr[256];
	static size_t tmp;
	char c;

	if('0' != x)
	{
		++arr[x];
		if((size_t)arr[x] > tmp)
		{
			tmp = arr[x];
			c = x;
		}	
	}
	else
	{
		printf("%c-%ld", c, tmp);
		memset(arr, 0, 256);
		tmp = 0;		
	}
}


int main()
{	
	int i;
	char test[] = {'a','s','d','e','e','v','a'};
	for(i =0; i < 7;++i) milion(test[i]);
	milion('a');
	milion('0');
	milion('0');


















return 0;
}
