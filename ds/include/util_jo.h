#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#define TEST_EQUAL(a, b) if ((a) != (b)) (size_t)printf("Fail at line #%d\n", __LINE__)

#ifndef NDEBUG
#define DEBUG_PRINT(str)    fprintf(stderr, str)
#else
#define DEBUG_PRINT(str)
#endif

#endif

