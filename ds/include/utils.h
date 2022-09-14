#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

#define TEST(a, b) ((a) != (b)) ? printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__) : puts("PASS");
#define DEAD (void*) 0xDEADBEEF


#ifndef NDEBUG
#define LOGERROR(str) fprintf(stderr, str);
#else
#define LOGERROR(str) 
#endif

#endif









