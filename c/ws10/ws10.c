
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> /* strlen */
#include <assert.h> /* assert*/


#define ASCII 48
#define ASCII2 65
#define ABC 26



int MyPow(int x, int y)
{
	int res = 1;
	while(y)
	{
		res = res * x;
		--y;
	}
	return res;
}

int HelperCount(int x)
{
	int res = 0;
	if(x < 0)
	{
		x *= - 1;
		res+=1;
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
	int res = 0;
	if(x < 0)
	{
		x *= -1;
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
	else if (c >= 'A' && c <= 'Z')
	{
		return c - 'A' + 10;
	}

	return 0;
}


int AtoiBase10(const char *str)
{
	int result = 0;
	assert(str);
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
	int i = 0;
	char *ptr = NULL;
	assert(dest);
	if(n < 0)
	{
		n *= -1;
		
	}
	i += HelperCount(n);
	ptr = dest + i - 1;
	
	while(n)
	{
		ch = n % 10 + ASCII;
		*ptr-- = ch;
		n = n / 10;
	}
	ptr[i+1] = '\0';
	
}

int AtoiBase36(const char *str, int base)
{	
	int res = 0;
	int i = strlen(str) - 1;
	assert(str);	
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


void ItoaBase36(int n, char *dest, int base)
{
	char ch;
	int i;
	char *ptr = NULL;
	int tail;
	assert(dest);
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

	ptr[i + 1] = '\0';
}
/*
void PrintCommonForTwo(const char *arr1, const char *arr2, const char *arr3)
{
	int *temp = (int*)calloc(ABC, sizeof(int));
	
	if(NULL == temp)
	{
		
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}	
	assert(arr1);
	assert(arr2);
	assert(arr3);	
	
	while(*arr3)
	{
		temp[*arr3++ - ASCII2] = -1;
	}
	while(*arr2)
	{
		if( temp[*arr2 - ASCII2] == -1)
		{
			arr2++;
		}
		else
		{
			temp[*arr2 - ASCII2] = 1;
			arr2++;
		}
	}
	while(*arr1)
	{
		if(temp[*arr1 - ASCII2] == 1)
		{
			printf("%c ",*arr1);
			temp[*arr1 - ASCII2] = -1;
		}
		arr1++;	
	}
	printf("\n");
	
	free(temp);
}
*/


void PrintCommonForTwo(const char *arr1, const char *arr2, const char *arr3, size_t len1, size_t len2, size_t len3)
{	
	size_t i;
	int *temp = (int*)calloc(ABC, sizeof(int));
	
	if(NULL == temp)
	{
		
		printf("SORRY, NO MEMORY FOR YOU. ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__);
	}	
	assert(arr1);
	assert(arr2);
	assert(arr3);	
	
	for(i = 0; i < len3; ++i)
	{
		temp[arr3[i] - ASCII2] = -1;
	}
	for(i = 0; i < len2; ++i)
	{
		if( temp[arr2[i] - ASCII2] == -1)
		{
			/*empty*/
		}
		else
		{
			temp[arr2[i] - ASCII2] = 1;
		}
	}
	for(i = 0; i < len1; ++i)
	{
		if(temp[arr1[i] - ASCII2] == 1)
		{
			printf("%c ",arr1[i]);
			temp[arr1[i] - ASCII2] = -1;	
		}
			
	}
	printf("\n");
	
	free(temp);
}

int IsLittleEndian()
{
	union Data{
		short a;
		char arr;
	};
	union Data data;
	data.a = 1;
	return data.arr;
}










