#ifndef __WS9_H__
#define __WS9_H__

/* Sets the first n bytes of source to the value c.
Returns a pointer to source. Word boundry optimized.*/
void *MemSet(void *source, int c, size_t n);

/* Copies n bytes from the object pointed to by src to the object pointed to by dest.
Returns a pointer to dest. Word boundry optimized.*/
void *MemCpy(void *dest, const void *src, size_t n);

/* Copies n bytes of src to dest. Allows copying between objects that might overlap.
Returns a pointer to dest. Word boundry optimized.*/
void *MemMove(void *dest, const void *src, size_t n);


#endif
