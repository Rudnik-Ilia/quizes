#include <stdio.h>
#include <stdlib.h>

/*  test function utilizing attribute 'section' ".ctors"/".dtors"
    to create constuctors/destructors without assigned priority.
    (provided by Michael Ambrus in earlier answer)
*/

#define SECTION( S ) __attribute__ ((section ( S )))

void test() 
{
    printf("\n\ttest() utilizing -- (.section .ctors/.dtors) w/o priority\n");
}

void (*funcptr1)(void) SECTION(".ctors") = test;
void (*funcptr2)(void) SECTION(".ctors") = test;
void (*funcptr3)(void) SECTION(".dtors") = test;

/*  functions constructX, destructX use attributes 'constructor' and
    'destructor' to create prioritized entries in the .ctors, .dtors
    ELF sections, respectively.
    
    NOTE: priorities 0-100 are reserved
*/

void construct1() __attribute__ ((constructor));
void destruct1() __attribute__ ((destructor));

int init_some_function() 
{
    printf("\n  init_some_function() called by elf_init()\n");
    return 1;
}

// int elf_init()
// {
//     __asm__(".section .init \n call elf_init \n .section .text\n");

//     if(!init_some_function ())
//     {
//         exit (1);
//     }
    
//     printf ("\n  elf_init() -- (.section .init)\n");

//     return 1;
// }

void construct1() 
{
    printf ("\n      construct1() constructor -- (.section .ctors) priority 101\n");
}

void destruct1() 
{
    printf ("\n      destruct1() destructor -- (.section .dtors) priority 101\n\n");
}


int main() 
{
    printf("\n\t  [ main body of program ]\n");

    return 0;
}