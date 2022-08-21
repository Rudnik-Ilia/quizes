#ifndef __WS6_H__
#define __WS6_H__

#include <stddef.h>

/*Exercise 1*/
unsigned long Pow2(unsigned int x, unsigned int y);


/*Exercise 2-A*/
int IsPowOf2_Loop(unsigned int n);


/*Exercise 2-B*/
int IsPowOf2(unsigned int n);

/*Exercise 3*/
int AddsOne(int num);

/*Exercise 4*/
void PrintOnly3BitsOn(unsigned int arr[], size_t len);

/*Exercise 5-A*/
unsigned char ByteMirror_Loop(unsigned char c);

/*Exercise 5-B*/
unsigned char ByteMirror(unsigned char c);

/*Exercise 6-A*/
int Is2And6_On(unsigned char c);

/*Exercise 6-B*/
int It2or6_On(unsigned char c);

/*Exercise 6-C*/
unsigned char Swap3and5(unsigned char c);

/*Excercise 7*/
unsigned int ClosestDivBy16(unsigned int n);

/*Exercise 8*/
void Swap2NoTemp(int *x, int *y);

/*Exercise 9-A*/
size_t CountSetBits_Loop(unsigned int x);

/*Exercise 9-B*/
size_t CountSetBits(unsigned int x);

/*Exercise 10*/
void PrintFloatBits(float num);


size_t CountSetBits_1(unsigned int x);

#endif
