
#include <stdio.h>
#include <stdlib.h>

#define ASCII 48



int HelperCount(int x)
{
	int res;
	res = 0;
	while(x)
	{
		x = x / 10;
		++res;
	}
	return res;
}

int AtoiBase10(const char *str)
{
	int result = 0;
	while(*str)
	{
		result = result*10 + *str++ - '0';
	}
	return result;
}

void ItoaBase10(int n, char *dest)
{
	char ch;
	int i;
	char *ptr;
	
	 
	i = HelperCount(n);
	ptr = dest + i;
	ptr[i] = '\0';
	
	while(n)
	{
		ch = n % 10 + ASCII;
		*ptr-- = ch;
		n = n / 10;
	}


}

int main()
{	
	
	
	/*
	int i;
	char* buff = (char*)malloc(HelperCount(123));
	printf("%d\n", AtoiBase10("1234"));
	ItoaBase10(456, buff);
	
	for(i = 0; i < 4; ++i) printf("%c\n", buff[i]);
	*/
	
	printf("%d\n", HelperCount(12333445));
	
	
	
	
	
	



















return 0;
}



