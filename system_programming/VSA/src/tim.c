/*******************************************************
* Filename: vsa.c                                      *
* Purpose: Implementation of variabled-size allocator  *
* Title: Variabled-size allocator                      *
* Author: Timofey Dankevich                            *
* Date: 09.10.2022                                     *
* Reviewer: Ilia                                       *
* Review status: Not reviewed                          *
*******************************************************/

#include <string.h> /* memcmp */
#include <assert.h> /* assert */

#include "vsa.h"

#ifndef NDEBUG
    #define STRUCT_SIZE 16
#else
    #define STRUCT_SIZE 8
#endif

#define IS_INSUFFICIENT_MEMORY_SIZE(memory) (memory <= (STRUCT_SIZE * 2))
#define AVAILABLE_SIZE(memory) (memory - (STRUCT_SIZE * 2))

#define TO_SHIFT_NUMBER_BY_EIGHT(number) ((number >> 3) << 3)
#define TO_ALIGN_MEMORY(memory) TO_SHIFT_NUMBER_BY_EIGHT(memory)

#define OPPOSITE(number) ((0 <= number) ? number : -number)

#define MAGIC (void *)0xDEADBEEF

#define GET_VALUE(block) (block)->size

#define WORD sizeof(size_t)

typedef struct block_header block_header_t;

struct block_header
{
    long size;
    #ifndef NDEBUG
    void *is_free;
    #endif
};

static void VSADefragmentation(block_header_t *block);
static size_t GetAlignedBlockSize(size_t block_size);
static block_header_t *GetNextBlock(block_header_t *block);

vsa_t *VSAInit(void *memory, size_t mem_size)
{
    vsa_t *vsa = NULL;
    block_header_t *begin_block = NULL;
    block_header_t *end_block = NULL;

    assert(NULL != memory);

    if (IS_INSUFFICIENT_MEMORY_SIZE(mem_size))
    {
        return NULL;
    }

    mem_size = TO_ALIGN_MEMORY(mem_size);
    mem_size = AVAILABLE_SIZE(mem_size);

    begin_block = (block_header_t *)memory;
    begin_block->size = (long)mem_size;

    end_block = (block_header_t *)((char *)memory + mem_size + STRUCT_SIZE);
    end_block->size = 0;

    #ifndef NDEBUG
    begin_block->is_free = MAGIC;
    end_block->is_free = NULL;
    #endif
    
    vsa = (char *)memory;
    return vsa;
}

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
    block_header_t *interval_block = NULL;

    void *free_block = NULL;
    void *memory = NULL;

    long free_memory = 0;

    assert(NULL != vsa);

    block_size = GetAlignedBlockSize(block_size);

    memory = (void *)vsa;
    free_memory = GET_VALUE((block_header_t *)memory);

    VSADefragmentation((block_header_t *)memory);
    free_memory = GET_VALUE((block_header_t *)memory);
    while (0 != free_memory && (long)block_size > free_memory)
    {
        memory = (void *)GetNextBlock((block_header_t *)memory);
        VSADefragmentation((block_header_t *)memory);
        free_memory = GET_VALUE((block_header_t *)memory);
    }

    if (0 == free_memory)
    {
        return NULL;
    }

    free_block = (void *)((char *)memory + STRUCT_SIZE);

    ((block_header_t *)memory)->size = block_size * (-1);

    if (0 < (free_memory - (long)block_size))
    {
        interval_block = ((block_header_t *)((char *)memory + STRUCT_SIZE + block_size));
        interval_block->size = free_memory - (long)block_size - STRUCT_SIZE;
        #ifndef NDEBUG
        interval_block->is_free = MAGIC;
        ((block_header_t *)((char *)free_block - STRUCT_SIZE))->is_free = NULL;
        #endif
    }

    return free_block;
}

size_t VSACheckLargestBlock(vsa_t *vsa)
{
    void *memory = NULL;

    long block_size = 0;
    long max_value = 0;

    size_t iter = 0;

    assert(NULL != vsa);

    memory = (void *)vsa;
    block_size = GET_VALUE(((block_header_t *)memory));

    for (iter = 0; 0 != block_size; ++iter)
    {
        VSADefragmentation((block_header_t *)memory);
        block_size = GET_VALUE(((block_header_t *)memory));
        if (block_size > max_value)
        {
            max_value = block_size;
        }
        memory = (void *)((char *)memory + OPPOSITE(block_size) + STRUCT_SIZE);
    }

    return (size_t)max_value;
}

void VSAFree(void *block_to_free)
{
    block_header_t *curr_block = NULL; 

	assert(NULL != block_to_free);

    curr_block = (block_header_t*)((char*)block_to_free - STRUCT_SIZE);

	curr_block->size = OPPOSITE(curr_block->size);
	#ifndef ndebug
	curr_block->is_free = MAGIC;
	#endif
}

static size_t GetAlignedBlockSize(size_t block_size)
{
    size_t result = TO_SHIFT_NUMBER_BY_EIGHT(block_size);
    return (block_size > result) ? result + WORD : block_size;
}

static block_header_t *GetNextBlock(block_header_t *block)
{
	assert(NULL != block);
	return (block_header_t*)((char*)block + STRUCT_SIZE + (size_t)(OPPOSITE(GET_VALUE(block))));
}

static void VSADefragmentation(block_header_t *block)
{
    block_header_t *curr_block = NULL; 
	long next_value = 0; 

	assert(NULL != block);

    curr_block = block;
    if (0 == curr_block->size)
    {
        return;
    }
    next_value = GET_VALUE(GetNextBlock(curr_block));

	while(0 < GET_VALUE(curr_block) && 0 < next_value)
	{
		curr_block->size += next_value + STRUCT_SIZE;
        next_value = GET_VALUE(GetNextBlock(curr_block));
	}
}

