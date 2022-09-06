#include <stdio.h>  /* printf */

#include "../include/bitarray.h"



bit_array_t BitArraySetOn(bit_array_t bit_array, size_t index)
{
	return bit_array | 1 << index;

}
