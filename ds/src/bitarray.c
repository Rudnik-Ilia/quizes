#include <stdio.h>  /* printf */

#include "../include/bitarray.h"



bit_array_t BitArraySetOn(bit_array_t bit_array, size_t index)
{
	return bit_array | 1 << index;
}

bit_array_t BitArraySetOff(bit_array_t bit_array, size_t index)
{


}
bit_array_t BitArraySetAllOn(bit_array_t bit_array)
{


}

size_t BitArrayCountOn(bit_array_t bit_array)
{
	size_t temp = 0;
	while(bit_array)
	{
		temp+=bit_array&1;
		bit_array>>1;
	}
	return temp;
}

