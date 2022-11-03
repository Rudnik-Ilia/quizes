
#ifndef __UTILS_H__
#define __UTILS_H__


#include <stdio.h>

#define BEEF (void *)0xDEADBEEF
#define CAFE (void *)0xCAFEBABE
enum status {FAIL, SUCCESS};

#ifndef NDEBUG
#define LOGGER(str) fprintf(stderr, str)
#else
#define LOGGER(str)
#endif

#endif



