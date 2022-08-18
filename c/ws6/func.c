


#include <stddef.h>/*size_t*/
#include <stdio.h>/*printf*/


unsigned long Pow2(unsigned int x, unsigned int y)
{
	unsigned long res;
	res = x << y;

return res;
}

int IsPowOf2_Loop(unsigned int n)
{
	int i = 0;
	while(n > 0)
	{
		if((n & 1) == 1)
		{
			++i;
		}
		n = n >> 1;
	}
		
	if(1 == i)
	{
		return 1;
	}		
	return 0;
}
int IsPowOf2(unsigned int n)
{
	if( n!=0)
	{
		return (0 == (n & (n - 1)));
	}
	return 0;
}

int AddsOne(int num)
{
	int res;
	res = -~num;
	return res;

}

void PrintOnly3BitsOn(unsigned int arr[], size_t len)
{	
	size_t i;
	size_t j;
	unsigned int mask;
	int count;
	mask = 1;
	for(i = 0; i < len; ++i)
	{	
		count = 0;
		mask = 1;
		for(j = 0; j < 8; ++j)
		{
			if((arr[i]&mask) == mask)
			{
				++count;	
			}
			mask = mask << 1;
		}
		if(count == 3)
		{
			printf("%d\n", arr[i]);
		}
	}
}
unsigned char ByteMirror_Loop(unsigned char c)
{
	unsigned char temp;
	unsigned char mask_1;
	unsigned char mask_2;
	size_t i;

	temp = 0;
	mask_1 = 1;
	mask_2 = 128;
	
	for(i = 0; i < 8; ++i)
	{
		if((c & mask_1) == mask_1)
		{
			temp = temp | mask_2;
			mask_2 = mask_2 >> 1;
			mask_1 = mask_1 << 1;
		}else
		{
			mask_2 = mask_2 >> 1;
			mask_1 = mask_1 << 1;
		}
	}
	return temp;
}


int Is2And6_On(unsigned char c)
{
	int bit_2;
	int bit_6;
	bit_2 = 2;
	bit_6 = 6;
	
	return ((c & (1<<bit_2)) && (c & (1<<bit_6))) ;
}

int It2or6_On(unsigned char c)
{
	int bit_2;
	int bit_6;
	bit_2 = 2;
	bit_6 = 6;

  	return ((c & (1<<bit_2)) || (c & (1<<bit_6))) ;
}
unsigned char Swap3and5(unsigned char c)
{

	int x;
	int mask_on_3;
	int mask_on_5;
	x = 0;
	mask_on_3 = (c >> 2) & 1;
	mask_on_5 = (c >> 4) & 1;
	x = mask_on_3 ^ mask_on_5;

 	return (c ^ (x<< 2 |x << 4));
 	
 	

}


























