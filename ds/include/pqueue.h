#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stddef.h> /* size_t */

typedef struct priority_queue pq_t;


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
pq_t *PQCreate(int(*priority_cmp_func)(const void *data1, const void *data2));


/*
 * Description: The function destroys the priority queue
 * Parameters: @pqueue is a pointer to an instance of priority queue
 * Return: -
 * Time complexity: O(n)
 */
void PQDestroy(pq_t *pqueue);


/*
 * Description: The function adds an element to the queue as the last element with the same priority
 * Parameters:  @pqueue is a pointer to the priority queue; @data is a pointer to the data
 * that will be put to the priority queue as the last element with the same priority
 * Return: 0 on success, 1 on failure
 * Time complexity: O(1)
 */
int PQEnqueue(pq_t *pqueue, void *data);


/*
 * Description: The function dequeues the first element in the priority queue (first element with the highest priority).
 * If the priority queue is empty - undefined bahavior
 * Parameters: @pqueue is a pointer to the priority queue
 * Return: a pointer to the dequeued value
 * Time complexity: O(1)
 */
void *PQDequeue(pq_t *pqueue);


/*
 * Description: The function allows to get data from the first element with the highest priority (front element). 
 * If queue is empty, undefined behaviour
 * Parameters: @queue is a pointer to instance of priority queue
 * Return: a pointer to the value
 * Time complexity: O(1)
 */
void *PQPeek(const pq_t *pqueue);


/*
 * Description: The function checks if the priority queue is empty
 * Parameters:  @queue is a pointer to instance of priority queue
 * Return: bool - 1 - true, 0 - false
 * Time complexity: O(1)
 */
int PQIsEmpty(const pq_t *pqueue);

/*
 * Description: The function returns the current size of the priority queue
 * Parameters: pqueue is a pointer to instance of priority queue
 * Return: size of priority queue
 * Time complexity: O(n)
 */
size_t PQSize(const pq_t *pqueue);


/*
 * Description: The function merges both pqueues to the dest priority queue.
 * After merge src is a valid empty pqueue
 * Parameters:  dest, src are pointers to instances of a pqueue
 * Return: a pointer to dest
 * Time complexity: O(1)
 */
pq_t *PQMerge(pq_t *dest, pq_t *src);

/*
 * Description: The function flushes the queue - pqueue remains a valid empty pqueue
 * Parameters: @pqueue, the queue to be flushed
 * Return: nothing
 * Time complexity: O(n);
 */

void PQFlush(pq_t *pqueue);

/*
 * Description: The function finds and removes a specified element from priority queue
 * Parameters: 
 *  @pqueue, a pointer to an instance of the priority queue
 *  @is_match, matching function to find the element to be removed   
 *  @params, value to be matched against is_match
 * Return: returns data of the element that was removed
 * Time complexity: O(n)
 */
void *PQErase(pq_t *pqueue, int (*is_match)(const void *data, void *params), void *params);

#endif /* __PQUEUE_H__ */
