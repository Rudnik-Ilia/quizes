/**
 * UTILITY HEADER
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>  /* fprintf, stderr */
#include <string.h> /* strrchr */

#define DEFAULT "\033[0m"

#ifndef __BOOL_STATUS_ENUMS__
#define __BOOL_STATUS_ENUMS__
typedef enum { FALSE = 0, TRUE = 1 } bool_t;
typedef enum status_e { SUCCESS = 0, FAILURE = 1 } status_t;
#endif

/*----------------------------------------------------------------------------
 *                            Common Macros                                 *
 *---------------------------------------------------------------------------*/

/* IDENTIFIERS */
#define AND         &&
#define OR          ||
#define NOT         !
#define IS          =
#define EQUALS      ==
#define NOTEQUALS   !=

/* TYPES */
#define INT16   short
#define UINT16  unsigned short
#define INT32   int
#define UINT32  unsigned int
#define INT64   long long
#define UINT64  unsigned long long

/* MISC */
#define UNUSED(p)       (void)p
#define WORDSIZE        sizeof(size_t)
#define SWAP(a, b)      (void *t = NULL; (t)=(a); (a)=(b); (b)=(t))

/* MATH */
#define MIN(x, y)           (((x) < (y)) ?  (x) : (y))
#define MAX(x, y)           (((x) > (y)) ?  (x) : (y))
#define ABS(x)              (((x) <  0) ? -(x) : (x))
#define DIFF(a,b)           ABS((a)-(b))
#define ARRAY_SIZE(a)       (sizeof(a) / sizeof(*a))
#define IS_ODD( num )       ((num) & 1)
#define IS_EVEN( num )      (!IS_ODD( (num) ))
#define IS_BETWEEN(n,L,H)   ((unsigned char)((n) >= (L) && (n) <= (H)))
#define IMPLIES(x, y)       (!(x) || (y)) 
/* i.e. foo(arr[], size) { assert(IMPLIES(n > 0, arr != NULL)); */

/* BITS */
#define BIT(x)          (1<<(x))
#define SETBIT(x,p)     ((x)|(1<<(p)))
#define CLEARBIT(x,p)   ((x)&(~(1<<(p))))
#define GETBIT(x,p)     (((x)>>(p))&1)
#define TOGGLEBIT(x,p)  ((x)^(1<<(p)))

/*----------------------------------------------------------------------------
 *                             Magic Numbers                                 *
 *---------------------------------------------------------------------------*/
#define DEADNULL        (void *)0xDEADDEAD
#define DEADBEEF        (void *)0xDEADBEEF
#define DECAFBAD        (void *)0xDECAFBAD
#define BAADF00D        (void *)0xBAADF00D

/*----------------------------------------------------------------------------
 *                              Debugging                                    *
 *---------------------------------------------------------------------------*/
#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifndef NDEBUG
#include <errno.h>
#define LOGERROR(format)                                   \
    do                                                     \
    {                                                      \
        fprintf(stderr, DEFAULT "DEBUG | %s:%d:" format " | %s\n", \
                __FILENAME__, __LINE__, strerror(errno));  \
        errno = 0;                                         \
        fflush(stderr);                                     \
    } while (0)
#else
#define LOGERROR(format) (void)0
#endif

#ifndef NDEBUG
#define UNIMPLEMENTED(func)                                         \
    do                                                              \
    {                                                               \
        fprintf(stderr, "%s:%d: " func " is not implemented yet\n", \
                __FILENAME__, __LINE__);                            \
        /* abort(); - maybe */                                      \
    } while (0)
#else
#define UNIMPLEMENTED(func) (void)0
#endif

#endif /* __UTILS_H__ */
