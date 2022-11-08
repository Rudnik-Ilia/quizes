#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h> /* printf, fputs, FILE */
#include <assert.h>

#define DEFAULT     "\033[0m"
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define TEST_EQUAL(a, b) \
	if ((a) != (b)) \
		printf("TEST FAILED ON STRING #%d\n", __LINE__);

#define IF_TRUE(expr, cond) (cond) == 1 ? (expr) : (void)0

#ifndef NDEBUG
#define ON_DEBUG(expr) (expr)
#else
#define ON_DEBUG(expr)
#endif /* NDEBUG */


#define PRINT_ERR(file, fun_name, err_desc) \
	fprintf(file, BOLDWHITE "[err] %s: %s: %s on line #%d\n" DEFAULT,\
			__FILE__, fun_name, err_desc, __LINE__)


#ifndef NDEBUG
#include <errno.h>
#define LOG_ERR(file, fun_name, err_desc) \
	fprintf(file, BOLDWHITE "[errno #%d] %s: %s: %s on line #%d\n" DEFAULT,\
			errno, __FILE__, fun_name, err_desc, __LINE__)
#else
#define LOG_ERR(file, fun_name, err_desc)
#endif /* NDEBUG */


#define SIZEOF_ARR(arr) sizeof(arr) / sizeof(arr[0])


/* 
 * VALIDATE is macro that asserts @count pointers from first.
 * Pointers should be stored in memory consecutive.
 */
#ifndef NDEBUG
#include <assert.h>
#define VALIDATE(first, count) \
	switch (count) \
	{ \
		case 6: assert(NULL != *((void**)((char*)&first - sizeof(void*) * 5))); \
		case 5: assert(NULL != *((void**)((char*)&first - sizeof(void*) * 4))); \
		case 4: assert(NULL != *((void**)((char*)&first - sizeof(void*) * 3))); \
		case 3: assert(NULL != *((void**)((char*)&first - sizeof(void*) * 2))); \
		case 2: assert(NULL != *((void**)((char*)&first - sizeof(void*)))); \
		case 1: assert(NULL != first); \
	}
#else
#define VALIDATE(first, count)
#endif /* NDEBUG */


#endif /* __UTILS_H__ */
