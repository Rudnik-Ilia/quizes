#ifndef __BITARRAY_H__
#define __BITARRAY_H__

typedef size_t bit_array_t;

/*
 * Description: The function allows to set on particular bit in an instance of bit array
 * Parameters: bit_array: an instance of bit array, index: a number of bit [0 .. 63]
 * Return: bit_array_t: an instance of bit array
 * Complexity: O(1)
*/
bit_array_t BitArraySetOn(bit_array_t bit_array, size_t index);

/*************************************************************/

/*
 * Description: The function allows to set off particular bit in an instance of bit array
 * Parameters: bit_array: an instance of bit array, index: a number of bit [0 .. 63]
 * Return: bit_array_t: an instance of bit array
 * Complexity: O(1)
*/
bit_array_t BitArraySetOff(bit_array_t bit_array, size_t index);

/*************************************************************/

/*
 * Description: The function allows to set on all bits in an instance of bit array
 * Parameters: bit_array: an instance of bit array
 * Return: bit_array_t: an instance of bit array
 * Complexity: O(1)
*/
bit_array_t BitArraySetAllOn(bit_array_t bit_array);

/*************************************************************/

/*
 * Description: The function allows to set off all bits in an instance of bit array
 * Parameters: bit_array: an instance of bit array
 * Return: bit_array_t: an instance of bit array
 * Complexity: O(1)
*/
bit_array_t BitArraySetAllOff(bit_array_t bit_array);

/*************************************************************/

/*
 * Description: The function allows to get particular bit value by index from an instance of bit array
 * Parameters: bit_array: an instance of bit array, index: a number of bit [0 .. 63]
 * Return: bit: obtained bit
 * Complexity: O(1)
*/
int BitArrayGetBit(bit_array_t bit_array, size_t index);

/*************************************************************/

/*
 * Description: The function allows to toggle bit value by index in an instance of bit array 
 * Parameters: bit_array: an instance of bit array, index: a number of bit [0 .. 63]
 * Return: bit_array_t: an instance of bit array
 * Complexity: O(1)
*/
bit_array_t BitArrayFlipBit(bit_array_t bit_array, size_t index);

/*************************************************************/

/*
 * Description: The function allows to mirror bits in an instance of bit array
 * Parameters: bit_array: an instance of bit array
 * Return: bit_array_t: an instance of bit array
 * Complexity: 
*/
bit_array_t BitArrayMirrorBits(bit_array_t bit_array);

/*************************************************************/

/*
 * Description: The function allows to rotate bit array to the right n steps to the right
 * Parameters: bit_array: an instance of bit array, n: steps
 * Return: bit_array_t: an instance of bit array
 * Complexity: O(?)
*/
bit_array_t BitArrayRotateRight(bit_array_t bit_array, size_t n);

/*************************************************************/

/*
 * Description: The function allows to rotate bit array to the left n steps to the left
 * Parameters: bit_array: an instance of bit array, n: steps
 * Return: bit_array_t: an instance of bit array
 * Complexity: O(?)
*/
bit_array_t BitArrayRotateLeft(bit_array_t bit_array, size_t n);

/*************************************************************/

/*
 * Description: The function allows to count how many bits are set
 * Parameters: bit_array: an instance of bit array
 * Return: size_t n: a number of set bits
 * Complexity: O(log n) or O(1)
*/
size_t BitArrayCountOn(bit_array_t bit_array);

/*************************************************************/

/*
 * Description: The function allows to count how many bits are off
 * Parameters: bit_array: an instance of bit array
 * Return: size_t n: a number of off bits
 * Complexity: O(log n) or O(1)
*/
size_t BitArrayCountOff(bit_array_t bit_array);

/*************************************************************/

/*
 * Description: The function allows to convert an instance of bit array to the string representation
 * Parameters: bit_array: an instance of bit array; dest: a destination string
 * Return: char *: a string representation of an instance bit array; 
 * Complexity: O(1)
*/
char *BitArrayToString(bit_array_t bit_array, char *dest);

#endif