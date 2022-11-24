#ifndef _TESTS_H_
#define _TESTS_H_

#include <stdio.h>
#include <stddef.h>

extern size_t test_counter;
extern size_t success_counter;

#define TEST(a,b) if(a == b) { ++test_counter; ++success_counter;}\
	else {printf("Test on %d FAILED \n", __LINE__);\
	++test_counter;}

#define SHOWRESULTS {printf("Passed %lu out of %lu tests \n", success_counter, test_counter);}


#endif
