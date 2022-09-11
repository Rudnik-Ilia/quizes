#pragma once
#include <stdio.h>

#define #define TEST(a, b) ((a) != (b)) ? printf("TEST FAIL! ERROR AT LINE: %d IN FILE: %s\n ",__LINE__, __FILE__) : puts("PASS");

#define ERROR(str) fprintf(stderr, str)



