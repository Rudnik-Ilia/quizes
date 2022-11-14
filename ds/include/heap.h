#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;
typedef int (*cmp_func_t)(const void *data1, const void *data2);
typedef int (*is_match_t)(const void *data, const void *param);

/**
 * struct heap
 * {
 *      vector_t *heap_vector;
 *      int (*cmp_func)(const void *left, const void *right);
 * }
 */
 
/**
 * @brief: Creates an instance of a heap.
 * @params: cmp_func: defines type of the heap (min/max)
 *          element_size: size of elements in the heap
 *          capacity: initial capacity of a heap
 * @return: Pointer to heap_t struct
 * @complexity: O(1)
 */
heap_t *HeapCreate(cmp_func_t cmp_func, size_t element_size);

/**
 * @brief: Destroys an instance of a heap
 * @params: Pointer to heap
 * @return: Void
 * @complexity: O(n)
 */
void HeapDestroy(heap_t *heap);

/**
 * @brief: Pushes a new element to the heap.
 * @params: Pointer to the heap
 *          Constant pointer to data
 * @return: 0 if success; Non-zero if failed
 * @complexity: O(log n)
 */
int HeapPush(heap_t *heap, const void *data);

/**
 * @brief: Pops the min/max value from the heap. Min/max is defined by compare function
 * @params: Pointer to heap
 * @return: Void
 * @complexity: O(log n)
 */
void HeapPop(heap_t *heap);

/**
 * @brief: Returns the min/max element of the heap.
 * @params: Pointer to heap
 * @return: Pointer to min/max element
 * @complexity: O(1)
 */
void *HeapPeek(const heap_t *heap);

/**
 * @brief: Removes a specified element within the heap
 * @params: A pointer to the heap, 
 *          A pointer to the data to be removed
 * @return: Pointer to removed data
 * @complexity: O(log n)
 */
void *HeapRemove(heap_t *heap, void* data, is_match_t is_match, void *param);

/**
 * @brief: Returns the size of the heap.
 * @params: instance of the heap
 * @return: size of the heap
 * @complexity: O(1)
 */
size_t HeapSize(const heap_t *heap);

/**
 * @brief: Determines whether or not the heap is empty.
 * @params: A constant pointer to a heap instance
 * @return: 0 if true; 1 if false
 * @complexity: O(1)
 */
int HeapIsEmpty(const heap_t *heap);

/** 
 * static void HeapifyUp(heap_t *heap); 
 * static void HeapifyDown(heap_t *heap);
 */

#endif
