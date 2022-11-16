#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stddef.h> /* size_t */

typedef struct priority_queue heap_pq_t;


/* goes to src */
/* 
struct priority_queue  
{
    sorted_list_t *list;
};

*/

/*
 * Description: The function creates an instance of a priority queue
 * Parameters: @cmp_func - compares elements by their priority and affects order of elements inside the pqueue
 * @priority_cmp_func should return 0 if @data1 == @data2 (equal priority),
 * less than 0 if @data1 < @data2 (less priority),
 * and greater than 0 if @data1 > @data2 (greater priority)
 * Return: new instance of the priority queue
 * Time complexity: O(1)
 */
heap_pq_t *HeapPQCreate(int(*priority_cmp_func)(const void *data1, const void *data2));


/*
 * Description: The function destroys the priority queue
 * Parameters: @pqueue is a pointer to an instance of priority queue
 * Return: -
 * Time complexity: O(n)
 */
void HeapPQDestroy(heap_pq_t *pqueue);


/*
 * Description: The function adds an element to the queue as the last element with the same priority
 * Parameters:  @pqueue is a pointer to the priority queue; @data is a pointer to the data
 * that will be put to the priority queue as the last element with the same priority
 * Return: 0 on success, 1 on failure
 * Time complexity: O(n)
 */
int HeapPQEnqueue(heap_pq_t *pqueue, void *data);


/*
 * Description: The function dequeues the first element in the priority queue (first element with the highest priority).
 * If the priority queue is empty - undefined bahavior
 * Parameters: @pqueue is a pointer to the priority queue
 * Return: a pointer to the dequeued value
 * Time complexity: O(1)
 */
void *HeapPQDequeue(heap_pq_t *pqueue);


/*
 * Description: The function allows to get data from the first element with the highest priority (front element). 
 * If queue is empty, undefined behaviour
 * Parameters: @queue is a pointer to instance of priority queue
 * Return: a pointer to the value
 * Time complexity: O(1)
 */
void *HeapPQPeek(const heap_pq_t *pqueue);


/*
 * Description: The function checks if the priority queue is empty
 * Parameters:  @queue is a pointer to instance of priority queue
 * Return: bool - 1 - true, 0 - false
 * Time complexity: O(1)
 */
int HeapPQIsEmpty(const heap_pq_t *pqueue);

/*
 * Description: The function returns the current size of the priority queue
 * Parameters: pqueue is a pointer to instance of priority queue
 * Return: size of priority queue
 * Time complexity: O(n)
 */
size_t HeapPQSize(const heap_pq_t *pqueue);

/*
 * Description: The function flushes the queue - pqueue remains a valid empty pqueue
 * Parameters: @pqueue, the queue to be flushed
 * Return: nothing
 * Time complexity: O(n);
 */

void HeapPQFlush(heap_pq_t *pqueue);

/*
 * Description: The function finds and removes a specified element from priority queue
 * Parameters: 
 *  @pqueue, a pointer to an instance of the priority queue
 *  @is_match, matching function to find the element to be removed   
 *  @params, value to be matched against is_match
 * Return: returns data of the element that was removed
 * or NULL if element was not found (nothing was removed)
 * Time complexity: O(n)
 */
void *HeapPQErase(heap_pq_t *pqueue, int (*is_match)(const void *data, const void *params), void *params);

#endif /* __PQUEUE_H__ */

