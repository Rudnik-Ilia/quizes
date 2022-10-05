#ifndef __FSA_H__
#define __FSA_H__

typedef struct fsa fsa_t;


struct fsa{
	void *base;
	size_t offset;
	size_t block_size;
	size_t freespace;
}; 


/*
 * Description: The function returns an instanse of FSA
 * Parameters: @block_size is a size of each block
 *             @mem_size is amount of all bytes 
 *             @memory is a pointer to the start of preallocated memory
 * Return: Pointer to an instanse of FSA
 * Time complexity: O(n)
*/
fsa_t *FSAInit(void *memory, size_t mem_size, size_t block_size); 

/*
 * Description: The function returns a pointer to a memory adress
 * Parameters: @fsa instanse of fsa
 * Return: a pointer to the first free block
 * Time complexity: O(1)
*/
void *FSAAlloc(fsa_t *fsa);

/*
 * Description:  The function returns the number of free blocks
 * Parameters: @fsa An instanse of FSA
 * Return: size_t number of blocks
 * Time complexity: O(1)
*/
size_t FSACountFree(const fsa_t *fsa);

/*
 * Description:  The function returns the size of memory (in bytes) needed from the user
 * Parameters: @num_of_block is how many block user wants to get from FSA
 *             @size_of_blocks size of each wanted block
 * Return: size_t size of memory in bytes
 * Time complexity: O(1)
*/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);

/*
 * Description:  The function free memory of the block
 * Parameters: @fsa is a pointer to an instance of FSA
 *             @block_to_free is pointer to block that we need to free
 * Return: nothing
 * Time complexity: O(1)
*/
void FSAFree(fsa_t *fsa, void *block_to_free);


#endif /* __FSA_H__ */
