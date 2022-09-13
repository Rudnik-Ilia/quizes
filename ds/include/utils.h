#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

#define TEST(a, b) ((a) != (b)) ? printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__) : puts("PASS");

#define LOGERROR(str) fprintf(stderr, str);

#endif

