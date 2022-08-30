
#include <stdio.h>
#include <stdlib.h> /* assert */
#include <string.h> /* strlen */

#define ASCII 48

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
/*

void shifting2(int num, char arr[])
{	
	int i;
	int j;
	int k;
	char *p_an;
    char B[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int num2;
    int ssc[8];
    p_an = arr;
    for (i = 0; i < 8; i++)
    {
        num2 = num / 16;
        ssc[i] = num - (num2 * 16);
        num = num2;
    }
    for (j = 0; j < 8; j++)
    {
        for (k = 0; k < 16; k++)
        {
            if (ssc[j] == A[k])
                *p_an++ = B[k];
        }
 
    }
}
*/
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
	ptr = dest + i;
	ptr[i] = '\0';
	
	while(n)
	{
		ch = n % 10 + ASCII;
		*ptr-- = ch;
		n = n / 10;
	}
}

int HelpTo(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	return 0;
}


int AtoiBase36(char *str, int base)
{	
	int res = 0;
	int i = strlen(str) - 1;	
	while(*str)
	{ 
		if(HelpTo(*str) > base)
		{
			return 0;
		}
		res = res + HelpTo(*str++) * MyPow(base, i--);
			
	}
	return res;
}




int main()
{	
	
	/*
	int i;
	printf("%d\n", AtoiBase10("1s34"));
	
	char B[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char* buff = (char*)malloc(4);
	
	
	int num = 45678;
	char* buff = (char*)malloc(HelperCount(num));
	ItoaBase10(num, buff);
	
	printf("%d",AtoiBase36("8", 2));
	*/
	
	printf("%d",AtoiBase36("010101010", 2));
	
	
	
	
	
	
	



















return 0;
}



