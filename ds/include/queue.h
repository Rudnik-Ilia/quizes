#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct queue queue_t;


/*
 * Description: The function creates an instance of queue
 * Parameters: -
 * Return: new instance of queue
 * Time complexity: O(1)
 */
queue_t *QueueCreate();


/*
 * Description: The function destroys and obtained queue
 * Parameters: queue is a pointer to instance of queue
 * Return: function return nothing
 * Time complexity: O(n)
 */
void QueueDestroy(queue_t *queue);


/*
 * Description: The function puts data to the back of the queue
 * Parameters:  queue is a pointer to instance of queue; data is a pointer data
 * that will be puted to the back of the queue
 * Return: 0 on success, 1 on failure
 * Time complexity: O(1)
 */
int QueueEnqueue(queue_t *queue, void *data);


/*
 * Description: The function removes data from the front of the queue
 * Parameters:  queue is a pointer to instance of queue
 * Return: function returns nothing
 * Time complexity: O(1)
 */
void QueueDequeue(queue_t *queue);


/*
 * Description: The function allows to get data from the front of the queue
 * Parameters:  queue is a pointer to instance of queue
 * Return: a pointer to the value
 * Time complexity: O(1)
 */
void *QueuePeek(const queue_t *queue);


/*
 * Description: The function allows to know that queue is empty
 * Parameters:  queue is a pointer to instance of queue
 * Return: bool
 * Time complexity: O(1)
 */
int QueueIsEmpty(const queue_t *queue);


/*
 * Description: The function allows to get the current size of queue
 * Parameters:  queue is a pointer to instance of queue
 * Return: size of queue
 * Time complexity: O(n)
 */
size_t QueueSize(const queue_t *queue);


/*
 * Description: The function appends src to the back of dest  dest--->src
 * after appending src is valid empty queue
 * Parameters:  dest, src is a pointers to instance of queue
 * Return: return pointer to dest
 * Time complexity: O(1)
 */
queue_t *QueueAppend(queue_t *dest, queue_t *src);


#endif /* __QUEUE_H__ */
