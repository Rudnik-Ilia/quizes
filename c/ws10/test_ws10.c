
#include <stdio.h>
#include <stdlib.h> /* assert */
#include <string.h> /* strlen */

#define ASCII 48

union {
		int a;
		char b;
	} Data;



int MyPow(int x, int y)
{
	int res = 1;
	while(y)
	{
		res = res * x;
		y--;
	}
	return res;

}

int HelperCount(int x)
{
	int res;
	res = 0;
	if(x < 0)
	{
		x*=-1;
	}
	while(x)
	{
		x = x / 10;
		++res;
	}
	return res;
}

int HelperCount36(int x, int base)
{
	int res;
	res = 0;
	if(x < 0)
	{
		x*=-1;
	}
	while(x)
	{
		x = x / base;
		++res;
	}
	return res;
}

int HelpToChar(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	return 0;
}


int AtoiBase10(const char *str)
{
	int result = 0;
	while(*str)
	{
		if ((*str >= 'a') && (*str <='z'))
		{	
		 return 0;
		}
		result = result*10 + *str++ - '0';
	}
	return result;
}

void ItoaBase10(int n, char *dest)
{
	char ch;
	int i;
	char *ptr;
	if(n < 0)
	{
		n*=-1;
	}
	i = HelperCount(n);
	ptr = dest + i -1;
	
	while(n)
	{
		
		ch = n % 10 + ASCII;
		*ptr-- = ch;
		n = n / 10;
	}
	ptr[i+1] = '\0';
}

int AtoiBase36(char *str, int base)
{	
	int res = 0;
	int i = strlen(str) - 1;	
	while(*str)
	{ 
		if(HelpToChar(*str) > base)
		{
			return 0;
		}
		res = res + HelpToChar(*str++) * MyPow(base, i--);
			
	}
	return res;
}

void Indian(int x)
{
	union Data{
		int a;
		char arr[4];
	};
	union Data data;
	data.a = x;
	
	printf("%d\n", data.arr[4]);
}

int IsLittleEndian()
{
	int x = 1;
  	return *((int *) & x) == 0 ? 0 : 1;
}




void ItoaBase36(int n, char *dest, int base)
{
	char ch;
	int i;
	char *ptr;
	int tail;
	if(n < 0)
	{
		n*=-1;
	}
	i = HelperCount36(n, base);
	
	ptr = dest + i - 1;
	
	
	while(n)
	{
		tail = n % base;
		if(tail < 10)
		{
			ch = tail + ASCII;
			*ptr-- = ch;
			n = (n - tail)/base;
		}
		else
		{
			ch = tail + 87;
			*ptr-- = ch;
			n = (n - tail)/base;
		}
	}

	ptr[i+1] = '\0';
}





int main()
{	
	int i;
	int num = 1379;
	char* buff = (char*)malloc(HelperCount36(num,16)+1);
	
	ItoaBase36(num, buff, 36);
	
	printf("%s\n", buff); 
	Indian(1);
	
	
	
	
	
	/*
	printf("%d\n", AtoiBase10("1s34"));
	for(i=0; i < 10; ++i) printf("%c", buff[i]);
	

	
	char* buff = (char*)malloc(4);
	
	
	printf("%d",AtoiBase36("8", 2));
	printf("%d",AtoiBase36("010101010", 2));
	*/
	
	
	
	
	
	
	
	
	
	



















return 0;
}



