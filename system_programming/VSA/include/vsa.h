#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

typedef void vsa_t;

/*

struct block_header{
    long size;
    #ifndef NDEBUG....
    
};


*/
typedef struct block_header{

    	long size;
    
   	#ifndef NDEBUG
	
	#endif   
}block_t;
/*
 * Description: The function returns an instanse of VSA
 * Parameters: @memory is a pointer to the start of preallocated memory
 *             @mem_size is amount of all bytes 
 * Return: Pointer to an instanse of VSA
 * Time complexity: O(1)
*/
vsa_t *VSAInit(void *memory, size_t mem_size);

/*
 * Description: The function returns a pointer to a memory adress
 * Parameters: @vsa instanse of vsa
 *             @size a block_size of needee block
 * Return: a pointer to the block of memory with size equal @size
 * Time complexity: O(n)
*/
void *VSAAlloc(vsa_t *vsa, size_t block_size);

/*
 * Description:  The function returns the size of the largest block
 * Parameters: @vsa An instanse of VSA
 * Return: size_t size of the largest block
 * Time complexity: O(n)
*/
size_t VSACheckLargestBlock(vsa_t *vsa);

/*
 * Description:  The function frees the memory of the block
 * Parameters: @vsa is a pointer to an instance of vsa
 *             @block_to_free is a pointer to the block that we need to free
 * Return: nothing
 * Time complexity: O(1)
*/
void VSAFree(void *block_to_free);


#endif /* __VSA_H__ */
