#include <stdio.h>  /* printf */

#include <limits.h> /* CHARBIT */
#include <assert.h> /* assert */
#include <string.h> /* strrev */
#include "../include/bitarray.h"

#define WORD 64
#define ASCII 48
#define BYTE8_1 	0x00000000000000FF 

static unsigned long int lookup[256] = 
{
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};

static unsigned int lut[256] = 
{
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
	 B6(0), B6(1), B6(1), B6(2)
};





bit_array_t BitArraySetOn(bit_array_t bit_array, size_t index)
{
	assert (index <= CHAR_BIT * sizeof(bit_array_t));
	return bit_array | 1lu << index;
}


bit_array_t BitArraySetOff(bit_array_t bit_array, size_t index)
{
	assert (index <= CHAR_BIT * sizeof(bit_array_t));
	return bit_array & ~(1lu << index);
}


bit_array_t BitArraySetAllOff(bit_array_t bit_array)
{
	(void)bit_array;
	return 0lu;
}

bit_array_t BitArraySetAllOn(bit_array_t bit_array)
{
	(void)bit_array;
	return -1lu;
}

bit_array_t BitArrayFlipBit(bit_array_t bit_array, size_t index)
{
	assert (index <= CHAR_BIT * sizeof(bit_array_t));
	return bit_array ^ (1lu << index);
}


size_t BitArrayCountOn(bit_array_t bit_array)
{
	size_t temp = 0;
	
	while(bit_array)
	{
		temp+=bit_array&1;
		bit_array = bit_array >> 1;
	}
	return temp;
}

size_t BitArrayCountOff(bit_array_t bit_array)
{
	return WORD - BitArrayCountOn(bit_array);
}

bit_array_t BitArrayMirrorBits(bit_array_t bit_array)
{
	bit_array = ((bit_array & 0x5555555555555555) << 1) | ((bit_array & 0xaaaaaaaaaaaaaaaa) >> 1);
	bit_array = ((bit_array & 0x3333333333333333) << 2) | ((bit_array & 0xcccccccccccccccc) >> 2);
    bit_array = ((bit_array & 0x0f0f0f0f0f0f0f0f) << 4) | ((bit_array & 0xf0f0f0f0f0f0f0f0) >> 4);
    bit_array = ((bit_array & 0x00ff00ff00ff00ff) << 8) | ((bit_array & 0xff00ff00ff00ff00) >> 8);
	bit_array = ((bit_array & 0x0000ffff0000ffff) << 16) | ((bit_array & 0xffff0000ffff0000) >> 16);

	return (bit_array  << 32) | (bit_array  >> 32);

}

bit_array_t BitArrayRotateRight(bit_array_t bit_array, size_t n)
{
	return (bit_array >> n) | (bit_array << (WORD - n));
}


bit_array_t BitArrayRotateLeft(bit_array_t bit_array, size_t n)
{
	return (bit_array << n) | (bit_array >> (WORD - n));
}


int BitArrayGetBit(bit_array_t bit_array, size_t index)
{
	assert (index <= CHAR_BIT * sizeof(bit_array_t));
	return 1lu & (bit_array >> index);
}
/* help function */
void reverse_string(char *str)
{
	
    char *start = str;
    char *end = start + strlen(str) - 1;
    char temp;
    assert(str);

    while (end > start)
    {
       
        temp = *start;
        *start = *end;
        *end = temp;

        ++start;
        --end;
    }
}

char *BitArrayToString(bit_array_t bit_array, char *dest)
{

	while(bit_array)
	{
		*dest++ = (char)((bit_array & 1) + ASCII);
		bit_array>>=1;
	}
	*dest = '\0';
	
	reverse_string(dest);
	return dest;
}

bit_array_t BitArraySetBit(bit_array_t bit_array, size_t index, int state)
{
	assert (index <= CHAR_BIT * sizeof(bit_array_t));
	if(state == 1)
	{
		return bit_array | (1lu << index);
	}
	else 
	{
		return bit_array & (~(1lu << index));
	}
}

bit_array_t BitArrayMirrorBitsLUT(bit_array_t bit_array)
{
	bit_array_t reverse = 0;
	reverse = (lookup[bit_array & BYTE8_1] << 56) | 
    (lookup[(bit_array >>  8) & BYTE8_1] << 48) | 
    (lookup[(bit_array >> 16) & BYTE8_1] << 40) |
    (lookup[(bit_array >> 24) & BYTE8_1] << 32) |
  	(lookup[(bit_array >> 32) & BYTE8_1] << 24) |
    (lookup[(bit_array >> 40) & BYTE8_1] << 16) |
    (lookup[(bit_array >> 48) & BYTE8_1] <<  8) |
    (lookup[(bit_array >> 56) & BYTE8_1]);
	return reverse;
}


size_t BitArrayCountOnLUT(bit_array_t bit_array)
{
	return  lut[bit_array & 0xff] + lut[bit_array>>8 & 0xff]+
		 	lut[bit_array>>16 & 0xff] + lut[bit_array>>24 & 0xff] +
		    lut[bit_array>>32 & 0xff] +	lut[bit_array>>40 & 0xff] +
		    lut[bit_array>>48 & 0xff] + lut[bit_array>>56 & 0xff];
}








