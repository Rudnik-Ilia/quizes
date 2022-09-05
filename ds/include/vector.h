#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct vector vector_t;


/*
 * Description: The function allows to create an instance of vector
 * Parameters: element_size: a size of an element in bytes; capacity: a length of an instance vector
 * Return: new instance of vector
 * Time complexity: 
 * Average: O(1)
 */
vector_t *VectorCreate(size_t element_size, size_t capacity);

/*****************************************************************************/

/*
 * Description: The function allows to destroy an obtained vector
 * Parameters: vec: an instance of vector
 * Return: nothing
 * Time complexity: 
 * Average: O(1)
 */
void VectorDestroy(vector_t *vector);

/*****************************************************************************/

/*
 * Description: The function allows to push an element at the end of vector
 * Parameters: vec: an instance of vector; data: a pointer to element
 * Return: 0: FAILED; 1: SUCCESSED
 * Time complexity: 
 * Average: O(1)
 * Worst case: O(n)

 * (To create an enum status_t)
 */
int VectorPushBack(vector_t *vector, const void *data);

/*****************************************************************************/

/*
 * Description: The function allows to pop the element from the end of vector
 * Parameters: vec: an instance of vector
 * Return: nothing
 * Time complexity: 
 * Average: O(1)
 */
void VectorPopBack(vector_t *vector);

/*****************************************************************************/

/*
 * Description: The function allows to get a size of the obtained vector
 * Parameters: vec: an instance of vector
 * Return: size_t: a current size of vector
 * Time complexity: 
 * Average: O(1)
 */
size_t VectorSize(const vector_t *vector);

/*****************************************************************************/

/*
 * Description: The function allows to obtain current capacity of the instance vector
 * Parameters: vector: an instance of vector
 * Return: size_t: a current vector's capacity
 * Time complexity: 
 * Average: O(1)
 */
size_t VectorCapacity(const vector_t *vector);

/*
 * Description: The function allows to get known whether the vector is empty or not
 * Parameters: vec: an instance of vector
 * Return: 1: a vector is empty, 0: a vector is not empty
 * Time complexity: 
 * Average: O(1)
 */
int VectorIsEmpty(const vector_t *vector);

/*****************************************************************************/

/*
 * Description: The function allows to set a value by index
 * Parameters: vec: an instance of vector; index: an index into the vector; data: a pointer to data
 * Return: nothing
 * Time complexity: 
 * Average: O(1)
 */
void VectorSetElement(vector_t *vector, size_t index, const void *data);

/*****************************************************************************/

/*
 * Description: The function allows to get a value by index
 * Parameters: vec: an instance of vector; index: an index into the vector
 * Return: void *: a pointer to the value
 * Time complexity: 
 * Average: O(1)
 */
void *VectorGetAccessToElement(const vector_t *vector, size_t index);

/*****************************************************************************/

/*
 * Description: The function allows to resize an instance of vector
 * Parameters: vec: an instance of vector; new_size: a new size of the vector
 * Return: vector_t *: a pointer to a new vector with new capacity
 * Time complexity: 
 * Average: O(n)
 */
vector_t *VectorReserve(vector_t *vector, size_t new_capacity);

/*****************************************************************************/

/*
 * Description: The function allows to shrink the size of vector
 * Parameters: vec: an instance of vector
 * Return: vector_t *: a pointer to a new instance of vector
 * Time complexity: 
 * Average: O(n)
 */
vector_t *VectorShrink(vector_t *vector);

#endif
