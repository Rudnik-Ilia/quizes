#ifndef __CBUFF_H__
#define __CBUFF_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

typedef struct cbuff cbuff_t;

/*
 * Description: The function creates a new instance of a circular buffer
 * Parameters: capacity is capacity in bytes of a new circular buffer
 * Return: pointer to the new instance of circular buffer or NULL if an error occurs
 * Time complexity: O(1)
 */
cbuff_t *CBuffCreate(size_t capacity);


/*
 * Description: The function destroy an given circular buffer
 * Parameters: cbuff is a pointer to the circular buffer
 * Return: function returns nothing
 * Time complexity: O(1)
 */
void CBuffDestroy(cbuff_t *cbuff);


/*
 * Description: The function writes num_of_bytes bytes from the src to the circular buffer
 * that cbuff points to
 * Parameters: cbuff is a pointer to the circular buffer, src is a pointer to the source,
 * num_of_bytes is a number of bytes to write from the source to circular buffer
 * Return: number of bytes that actually was written to the circular buffer
 * or -1 if an error occurs
 * Time complexity: O(n)
 */
ssize_t CBuffWrite(cbuff_t *cbuff, const void *src, size_t num_of_bytes);


/*
 * Description: The function reads num_of_bytes bytes to the dest from the circular buffer
 * that cbuff points to
 * Parameters: cbuff is a pointer to the circular buffer, dest is a pointer to the destination,
 * num_of_bytes is a number of bytes to read from the circular buffer to the dest
 * Return: number of bytes that actually was read from the circular buffer
 * or -1 if an error occurs
 * Time complexity: O(n)
 */
ssize_t CBuffRead(cbuff_t *cbuff, void *dest, size_t num_of_bytes);


/*
 * Description: The function checks if the given circular buffer is empty
 * Parameters: cbuff is a pointer to the circular buffer
 * Return: bool
 * Time complexity: O(1)
 */
int CBuffIsEmpty(const cbuff_t *cbuff);


/*
 * Description: The function allows to know how many bytes of free space in the circular buffer
 * Parameters: cbuff is a pointer to the circular buffer
 * Return: how much free space in bytes
 * Time complexity: O(1)
 */
size_t CBuffFreeSpace(const cbuff_t *cbuff);


/*
 * Description: The function allows to know how much space in the circular buffer
 * Parameters: cbuff is a pointer to the circular buffer
 * Return: how much space in bytes
 * Time complexity: O(1)
 */
size_t CBuffCapacity(const cbuff_t *cbuff);

#endif /* __CBUFF_H__ */
