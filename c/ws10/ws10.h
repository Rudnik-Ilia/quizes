#ifndef __WS10_H__
#define __WS10_H__


/*count amoumt of numbers */
int HelperCount(int x);
/*count amoumt of numbers for diffrent base*/
int HelperCount36(int x, int base);

/* Converts the string argument str to an integer. Returns the converted integral number as an int value. */
int AtoiBase10(const char *str);

/* Coverts the integer n into a character string. The string is placed in the buffer passed, which must be large enough to hold the output. */
void ItoaBase10(int n, char *dest);


/* Similar to AtoiBase10, but base value can be any base up to 36 */
int AtoiBase36(const char *str, int base);

/* Similar to ItoaBase10, but base value can be any base up to 36 */
void ItoaBase36(int n, char *dest, int base);


/* Prints the letters that only appear in both the first two arrays, but not the third one. Does not
print the same character more than once. */
void PrintCommonForTwo(const char *arr1, const char *arr2, const char *arr3, size_t len1, size_t len2, size_t len3);

/* Checks whether your system is little-endian. Returns 1, if the system is little endian. */
int IsLittleEndian();


#endif
